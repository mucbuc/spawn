var assert = require( 'assert' )
  , Promise = require( 'promise' ) 
  , Printer = require( './printer' )
  , fs = require( 'graceful-fs' )
  , summary = '';

process.on( 'exit', function() {
  console.log( summary );
});

function Logic(base) {

  this.traverse = function(o) {
    return new Promise(function(resolve, reject) {
        try {
          fs.exists( o.testDir, function(exists) {
            if (exists) { 
              resolve( o ); 
            }
            else {
              Printer.cursor.red();
              process.stdout.write( 'invalid test definition path: ' + o.testDir );
              Printer.cursor.reset();
              reject();
            }
          });
        }
        catch(e)
        {
          Printer.printError( e );
          summarize( e, o );
          throw(e);
        } 
      });

  };

  this.generate = function(o) {
    return new Promise(function(resolve, reject) {
      Printer.begin( o.defFile, 'generate' );
      try {
        base.generate( o, function( exitCode, buildDir){
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
      }
      catch( e ) 
      {
        Printer.printError( e );
        summarize( e, o );
        throw( e );
      }
    });
  };

  this.build = function(o) {
    return new Promise( function(resolve, reject) {
      Printer.begin( o.defFile, 'build' );
      
      try {    
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
      }
      catch(e) 
      {
        Printer.printError( e );
        summarize( e, o );
        throw e;
      }
    });
  };

  this.run = function(o) {
    return new Promise(function(resolve, reject) {
      Printer.begin( o.defFile, 'run' );
      try {
        base.run( o, function(exitCode) {
          o['exitCode'] = exitCode;
          if (!exitCode) {
            Printer.finishGreen( o.defFile );
            resolve(o);
            summarize( " passed", o );
          }
          else {
            Printer.finishRed( o.defFile ) ; 
            reject(o);
          }
        });
      }
      catch(e) {
        Printer.printError(e);
        summarize( e, o );
        throw e;
      }
    });
  }; 
};

function summarize(e, o) {
  if (typeof e !== 'string') {
    e = e.toString();
  }
  summary += o.testDir + e + '\n';
}

module.exports = Logic;