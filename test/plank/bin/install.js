#!/usr/bin/env node

var assert = require( 'assert' )
  , events = require( 'events' )
  , cp = require( 'child_process' )
  , emitter = new events.EventEmitter()
  , Reader = require( './Reader' )
  , program = require( 'commander' ); 

program
	.version( '0.0.0' )
	.option( '-p, --prefix [path]', 'output path' )
	.parse( process.argv )

emitter.on( 'addSubtree', function( dependency, name ) {
	
	var child = cp.spawn( 'git', [
			'subtree',
			'add', 
			'-P',
			name, 
			name,
			'master', 
			'--squash'
		], {
			stdio: 'inherit'
		});

	child.on( 'exit', function(code) {
		emitter.emit( 'next dependency');
	} );

});

installDependencies( Reader.readDependencies() );

function installDependencies( dependencies, index ) {
	
	if (typeof index === 'undefined')
		index = 0;

	if (index < dependencies.length)
	{
		var child
		  , dependency = dependencies[ index ]
		  , name = Reader.libName( dependency );

		child = cp.spawn( 'git', [ 
				'remote',
				'add',
				'-f',
				name,
				dependency,
			], {
				stdio: 'inherit'
			} );

		emitter.once( 'next dependency', function() {
			installDependencies( dependencies, index + 1 );
		} ); 

		child.on( 'exit', function( code ) {
			if (!code) {
				console.log( 'remote added: ', name );
				emitter.emit( 'addSubtree', dependency, name );
			}
			else { 
				console.log( 'remote add failed: ', name );
				emitter.emit( 'next dependency');
			}
		});
	} 
}
	
