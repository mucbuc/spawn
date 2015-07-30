var assert = require( 'assert' )
  , Promise = require( 'promise' ) 
  , Printer = require( './printer' )
  , fs = require( 'graceful-fs' );

function Logic(base) {

  this.traverse = function(o) {
    return new Promise(function(resolve, reject) {
        fs.exists( o.testDir, function(exists) {
          if (exists) { 
            resolve( o ); 
          }
          else {
            Printer.cursor.red();
            process.stdout.write( 'invalid test definition path: ');
            Printer.cursor.reset();
            reject();
          }
        });
      });

  };

  this.generate = function(o) {
    return new Promise(function(resolve, reject) {
      Printer.begin( o.defFile, 'generate' );
      base.generate( o, 
        function( exitCode, buildDir){
          //o['buildDir'] = buildDir;
          o['testDir'] = o.testDir;
          if (!exitCode) {
            Printer.finishGreen( o.defFile, 'generate' );
            resolve(o);
          }
          else {
            Printer.finishRed( o.defFile ) ; 
            reject(o); 
          }
        });
      });
  };

  this.build = function(o) {
    return new Promise( function(resolve, reject) {
      Printer.begin( o.defFile, 'build' );
      base.build( o, function( o ) { 
        if (!o.exitCode) {
          Printer.finishGreen( o.defFile );
          resolve( o );
        }
        else {
          Printer.finishRed( o.defFile );
          reject(o); 
        }
      });
    });
  };

  this.run = function(o) {
    return new Promise(function(resolve, reject) {
      Printer.begin( o.defFile, 'run' );
      base.run( o, function(exitCode) {
        if (!exitCode) {
          Printer.finishGreen( o.defFile );
          console.log( '=> ' + o.target + ' passed' );
          o['exitCode'] = exitCode;
          resolve(o);
        }
        else {
          Printer.finishRed( o.defFile ) ; 
          console.log( '=> ' + o.target + ' failed with exit code:', exitCode );
          reject(o);
        }
      });
    });
  }; 
};

module.exports = Logic;