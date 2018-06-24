#!/usr/bin/env node

'use strict';

var test = require( 'tape' )
  , fs = require( 'fs' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Expector = require( 'expector' ).SeqExpector;

test( 'asserter', function(t) {
  var controller = new Expector(t)
   ,  resultPath = path.join( __dirname, 'tmp/result.json' ); 

  controller
  .expect( 'not exits' )
  .expect( 'exits' )
  .expect( 0 );

  fs.unlink( resultPath, function(err) {
    tryOpen();
    crimp([ './test.json', '-g' ], controller, tryOpen );
  } );
  
  function crimp(args, controller, cb) {

    var child = cp
    .spawn( 'crimp', 
            args, 
            { stdio: 'pipe', cwd: __dirname } )
    .on( 'exit', function(code) {
      
      if (typeof cb !== 'undefined') {
        cb();
      }
      controller.emit( code );
      controller.check(); 
    })
    .on( 'error', (error) => {
      console.log( 'error:', error ); 
    });

    return child;
  }

  function tryOpen() {
    try {
      fs.statSync( resultPath );
      controller.emit( "exits" );   
    }
    catch(err) {
      controller.emit( "not exits" );
    }
  } 

});
