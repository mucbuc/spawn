#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , events = require( 'events' )
  , path = require( 'path' )
  , fs = require( 'graceful-fs' )
  , emitter = new events.EventEmitter
  , util = require( 'util' )
  , ansi = require( 'ansi' )
  , cursor = ansi( process.stdout )
  , program = require( 'commander' )
  , copy = require( 'fs-extra' ).copy;

assert( typeof cp !== 'undefined' );
assert( typeof copy === 'function' );

program
	.version( '0.0.0' )
	.option( '-g, --gcc', 'use gcc compiler' )
	.parse( process.argv );

program.path = path.join( __dirname, '../..' );
program.output = path.join( __dirname, '../..', 'build' );

attachLogic( emitter );

console.log( program.output );

emitter.emit( 'traverse', program.path );

function attachLogic(emitter) {

	emitter.on( 'run', function( defFile, testDir, targetName ) {
		begin( defFile, 'run' );
		run( defFile, testDir, targetName, function(exitCode) {
			if (!exitCode) {
				finishGreen( defFile );
				console.log( '=> ' + targetName + ' passed' );
			}
			else {
				finishRed( defFile ) ; 
				console.log( '=> ' + targetName + ' failed with exit code:', exitCode );
			}
		});
	}); 

	emitter.on( 'build', function( defFile, testDir ) {
		begin( defFile, 'build' );
		build( defFile, testDir, function( exitCode, targetName, buildDir ) { 
			if (!exitCode) {
				finishGreen( defFile );
				emitter.emit( 'run', defFile, buildDir, targetName );
			}
			else {
				finishRed( defFile );
			}
		});
	});

	emitter.on( 'generate', function( defFile, testDir ) {
		begin( defFile, 'generate' );
		generate( defFile, testDir, function( exitCode, buildDir ){
			finishGreen( defFile, 'generate' );
			if (!exitCode) {
				emitter.emit( 'build', defFile, buildDir );
			}
		});
	});

	emitter.on( 'traverse', function(testDir) {
		
		fs.exists(testDir, function(exists) {
			if (exists) { 
				traverse( testDir, function(gypFile) {
					emitter.emit( 'generate', gypFile, testDir );
				});
			}
			else {
				cursor.red();
				process.stdout.write( 'invalid test definition path: ');
				cursor.reset();
				console.log( testDir ); 
			}
		});


	});

	function begin( msg1, msg2 ) {
		cursor.green();
		process.stdout.write( msg1 + ': ' );
		cursor.reset();
		console.log( msg2 );
		console.time( msg1 );
	}

	function finishGreen( msg1 ) {
		cursor.green();
		console.timeEnd( msg1 );
		cursor.reset();
	}

	function finishRed( msg1 ) {
		cursor.red();
		console.timeEnd( msg1 );
		cursor.reset();
	}

	function traverse( testDir, cb ) {
		fs.readdir( testDir, function( err, files ) {
				files.forEach( function( file ) {
					if (path.extname(file) == '.gyp') {
						cb( file ); 
					}
				} );	
			} );
	}

	function generate( defFile, defDir, cb ) {

		var buildDir = program.output;

		makePathIfNone(buildDir, function() {
			var include = program.gcc ? 'plank/def/cpp11-gcc.gypi' : 'plank/def/cpp11.gypi';
			var args = [
					defFile,
					'--depth=' + (program.gcc ? './' : '.'),
					'--generator-output=' + buildDir,
					'--include=' + include	
				];

			if (program.gcc) {
				args.push( '--format=make' );
			}

			console.log( args );

			cp.spawn( 
				'gyp', 
				args, {
					stdio: 'inherit',
					cwd: defDir
				})
			.on( 'close', function( code ) {
				cb( code, buildDir );
			});

		});

		function makePathIfNone( path, cb ) {
			fs.exists(path, function(exists) {
				if (exists) 
					cb();
				else 
					fs.mkdir( path, [], cb ); 
			});
		}
	}

	function build( defFile, buildDir, cb ) {
		readTargetName( defFile, program.path, function( targetName ) { 
			
			console.log( buildDir );
			var child; 
			if (program.gcc) {
				child = cp.spawn(
					'make',
					[ '-j'],
					{
						stdio: 'inherit',
						cwd: buildDir
					}); 
			}
			else {

				var args = [
					"-project",
					path.join( buildDir, targetName + '.xcodeproj' )
				];

				console.log( args, buildDir ); 

				child = cp.spawn( 
					'xcodebuild', 
					args, {
						cwd: buildDir,
						stdio: 'inherit'
					} ); 
			}

			child.on( 'close', function( code ) {
				cb( code, targetName, buildDir ); 
			} );
		} );
	}

	function run( defFile, testDir, target, cb ) {
		
		var execPath;
		if (program.gcc) {
			testDir = path.join( testDir, 'out' );
		}
		execPath = path.join( testDir, 'Default', target );
		
		console.log( execPath );
		
		cp.spawn( 
			execPath, 
			[], {
			stdio: 'pipe'
		})
		.on( 'close', function( code ) {
			cb( code );
		})
		.stdout.on( 'data', function( data ) {
			cursor.blue();
			process.stdout.write( defFile + ': ' ); 
			cursor.reset();
			console.log( data.toString() );
		});
	}

	function readTargetName(defFile, testDir, cb) {
		var defPath = path.join( testDir, defFile );
		fs.readFile( defPath, function( err, data ) {
			if (err) {
				cursor.red();
				process.stdout.write( defFile + ': ' );
				cursor.reset();
				console.log( err );
			}
			else {
				var matches = data.toString().match( /'target_name'\s*:\s*'(.*)'/ )
				if (matches) {
					cb( matches[1] );
				}
			}
		} ); 
	}
}
