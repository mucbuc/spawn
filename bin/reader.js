var assert = require( 'assert' )
  , path = require( 'path' )
  , m_ = require( '../m_.json' );

assert( m_.hasOwnProperty( 'dependencies' ) );

function readDependencies() {
	return m_.dependencies;
}

function libName( dependency ) {
	return 'lib/' + path.basename( dependency, '.git' ); 
}

module.exports.readDependencies = readDependencies;
module.exports.libName = libName;