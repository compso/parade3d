//-------------------------------------------------------------------
/**	\file    	main.cpp
	\date   	27.02.2009
	\author		Ash Retallack
	\brief      	This file registers and unregisters the mel commands \
			and the file translator when the plugin in loaded
			and un-loaded. 
 	\note       
		
		TODO :: 
			Options
**/ 
//--------------------------------------------------------------------------

#include "MayaFileTranslator.h"
#include <maya/MStatus.h>
#include <maya/MObject.h>
#include <maya/MFnPlugin.h>

#include <iostream>


// link to some fairly funky maya libs. NOTE: The Image library only became part of maya
// from version 4.01 onwards. It is not available in version 4.0
//
#ifdef WIN32
	#pragma comment(lib,"Foundation.lib")
	#pragma comment(lib,"OpenMaya.lib")
	#pragma comment(lib,"OpenMayaFx.lib")
	#pragma comment(lib,"Image.lib")
	#pragma comment(lib,"OpenMayaAnim.lib")
#endif


//-------------------------------------------------------------------
#ifdef WIN32
	#define MLL_EXPORT extern __declspec(dllexport) 
#else
	#define MLL_EXPORT
#endif

//-------------------------------------------------------------------


/// specifies a script to use for the user interface options box
char* g_OptionScript = "MayaFileExportScript";

/// a set of default options for the exporter
char* g_DefaultOptions = "-namesonly=0;";

//-------------------------------------------------------------------	initializePlugin
///	\brief	initializePlugin( MObject obj )
///	\param	obj		-	the plugin handle
///	\return	MS::kSuccess if ok
///	\note	Registers all of the new commands, file translators and new 
///			node types.
///
MLL_EXPORT MStatus initializePlugin( MObject obj )
{
	MStatus status;

	std::cout << "Parade3d -- Maya translater Plugin version 1.0" << std::endl;
	MFnPlugin plugin( obj, "Ashley Retallack", "1.0", "Any");

	// Register the translator with the system
	status =  plugin.registerFileTranslator( "Parade3d", "none",
		MayaFileTranslator::creator,
		(char*)g_OptionScript,
		(char*)g_DefaultOptions );  

	if (status != MS::kSuccess) {
		status.perror("MayaExportCommand::registerFileTranslator");
	}
	return status;
                                     
}


//-------------------------------------------------------------------	uninitializePlugin
///	\brief	uninitializePlugin( MObject obj )
///	\param	obj	-	the plugin handle to un-register
///	\return	MS::kSuccess if ok
///	\note	un-registers the plugin and destroys itself
///
MLL_EXPORT MStatus uninitializePlugin( MObject obj )
{
	MFnPlugin plugin( obj );
	MStatus status =  plugin.deregisterFileTranslator( "Parade3d" );
	if (status != MS::kSuccess) {
		status.perror("MayaExportCommand::deregisterFileTranslator");
	}

	return status;
}

