#!/usr/bin/env node

var assert = require( 'assert' )
  , events = require( 'events' )
  , path = require( 'path' )
  , fs = require( 'graceful-fs' )
  , program = require( 'commander' )
  , Base = require( './base' )
  , Logic = require( './logic' )
  , DateTime = require( 'date-time-string' ); 

assert( typeof Logic !== 'undefined' );

program
  .version( '0.0.0' )
  .option( '-p, --path [path]', 'test path' )
  .option( '-o, --output [path]', 'build output' )
  .option( '-g, --gcc', 'use gcc compiler' )
  .parse( process.argv );

program.path = program.path ? path.join( process.cwd(), program.path ) : process.cwd();
program.output = path.join( process.cwd(), program.output ? program.output : 'build' );

(function() {
  var base = new Base(program)
    , logic = new Logic( base )
    , emitter = new events.EventEmitter;
  
  emitter.on( 'run', function( o ) {
    logic.run( o )
    .then( function() { 
      log('passed');
    })
    .catch( function() {
      log('failed (test)');
    });
  }); 

  emitter.on( 'build', function( o ) {
    logic.build( o )
    .then( function( o ) {
      emitter.emit( 'run', o );
    })
    .catch( function() {
      log('failed (build)');
    });
  });

  emitter.on( 'generate', function( o ) {
    logic.generate( o )
    .then( function( o ) {
      emitter.emit( 'build', o );
    })
    .catch( function() {
      log('failed (generate)');
    });
  });

  emitter.on( 'traverse', function( o ) {
    logic.traverse( o ).then( function( o ) {
      base.traverse( o, function(defFile) {
        o['defFile'] = defFile;
        emitter.emit( 'generate', o );
      });
    });
  });

  emitter.emit( 'traverse', { testDir: program.path } );

  function log(msg) {
    var tmp = DateTime.toDateTimeString() + ": " + msg + '\n';
    fs.appendFile( 'build.log', tmp, function(err) {
      if (err) throw err;
    } ); 
  }

})();