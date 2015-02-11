#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , Reader = require( './Reader' );

function update( dependencies, index ) {
	if (typeof index === 'undefined') {
		index = 0;
	}

	if (index < dependencies.length) {
		var name = Reader.libName( dependencies[index] );
		cp.exec( 
			'git subtree pull -P ' + name + ' ' + name + ' master --squash', 
			function(error, stdout, stderr) {
				if (error) throw error;
				console.log( stdout );
				update( dependencies, index + 1 );
			} ); 
	}
}

update( Reader.readDependencies() ); 
