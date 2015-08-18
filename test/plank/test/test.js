#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Expector = require( 'expector' ).Expector
  , controller = new Expector(); 

controller.expect( 'built' ); 
controller.expect( 'hello\n' );

cp
.fork( path.join( __dirname, 'plank/bin/test.js' ) )
.on( 'exit', function() {
	controller.emit( 'built' );
	cp.execFile( path.join( __dirname, '/build/Test/test' ), function(err, stdout, stderr) {
		if(err) throw err;
		controller.emit( stdout );
	} ); 
});

process.on( 'exit', function() {
	controller.check();
});