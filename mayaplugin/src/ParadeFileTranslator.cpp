//-------------------------------------------------------------------
///	\file    	MayaFileTranslator.cpp
///	\date   	24/4/2004   16:39
///	\author		Rob Bateman
///	\brief      
/// \note       
/// 
/// 		This sourcefile is provided as-is and no guarentee or warrenty 
///			is provided for any damage that may arise from using it. This
///			code is free for your own use, the only thing i ask is a small
///			credit somewhere for my work. An e-mail saying you found it 
///			useful would also be much appreciated by myself ;)
///
///			If you find any bugs arising to maya version changes or you
///			have improvements to the source code, then feel free to mail
///			them to me and i'll update the source-code on the website.
///			Before you e-mail bug reports, make sure that it is my code 
///			causing the problem, and not some wierd oddity in the maya 
///			scene. This code is designed to handle most common model set-ups,
///			it is not designed to replicate perfectly everything that maya
///			does. 
/// 
///			DO NOT send me feature requests, i'm not likely to add to this
///			code myself unless something really new and groovy comes along.
///			This is mainly due to my current time restrictions. If you do
///			have code written that adds something fairly groovy to the 
///			exporter, then i will happily update the exporter code and give
///			full credit where due.....
/// 
///			Robert Bateman
/// 
///				email code to:    rbateman@bmth.ac.uk
///				contact:          robthebloke@hotmail.com
/// 
//--------------------------------------------------------------------------

#include <fstream>
#include <iostream>

#include "MayaFileTranslator.h"

#include <maya/MArgList.h>
#include <maya/MFileObject.h>
#include <maya/MFnDependencyNode.h>
#include <maya/MItDependencyNodes.h>
#include <maya/MObject.h>
#include <maya/MObjectArray.h>
#include <maya/MStatus.h>
#include <maya/MString.h>
#include <maya/MStringArray.h>

//	maya base class includes for your own defined gubbins
#include <maya/MPxFileTranslator.h>



//-------------------------------------------------------------------	MayaFileTranslator
///	\brief  ctor
///
MayaFileTranslator::MayaFileTranslator(void)
{
	m_bShort = false;
}

//-------------------------------------------------------------------	~MayaFileTranslator
///	\brief  dtor	
///
MayaFileTranslator::~MayaFileTranslator(void)
{
}


//-------------------------------------------------------------------	reader
///	\brief  This function reads the requested file into maya (import)
///	\param  file	-	info about the file, ie paths, filename etc
///	\param	options	-	mel passes options read from the user
///			interface through to the read function
/// \param	mode	-	ignore for reading
///
MStatus	MayaFileTranslator::reader( const MFileObject& file,
				   const MString& options,
				   FileAccessMode mode)
{
	std::cerr << "Read method as yet unimplimented\n" << std::endl;
	return MS::kFailure;
}

//-------------------------------------------------------------------	writer
///	\brief  Exports the scene data to a text file
///	\param  file	-	info about what to output
/// \param	options	-	a set of output options
/// \param	mode	-	all or selected
///	\return	status code
///
MStatus	MayaFileTranslator::writer( const MFileObject& file,
				   const MString& options,
				   FileAccessMode mode )
{
	MStatus     	stat;

	//	flags that are created by the option script
	//
	const MString	namesonlyFlag	("-namesonly");

	//	set initial default flags incase something has 
	//	gone wrong on the maya side
	//
	m_bShort		= true;


	//	process the option string passed in from the option script
	//
	if (options.length() > 0) 
	{
        int i, length;
        // Start parsing.
        MStringArray optionList;
        MStringArray theOption;

		//	each option is in the form -
		//	[Option] = [Value];
		//
		//	the options are therefore split by the semi-colons
		//
        options.split(';', optionList);

		//	process each option in the string
		//
		length = optionList.length();
			
		for( i = 0; i < length; ++i )
		{
            theOption.clear();

			//	split the option using the '=' character. This should make 
			//	theOption[0] hold the option name, and theOption[1] hold the
			//	value of the current option
			//
            optionList[i].split( '=', theOption );

            if( theOption[0] == namesonlyFlag && theOption.length() > 1 ) 
			{
		
                if(theOption[1].asInt()>0) 
					m_bShort = true;
				else 
					m_bShort = false;
            }
        }
	}
	
	// if this is true, then "Export Selected" was chosen in stead of "Export All"
	//
	if( mode == MPxFileTranslator::kExportActiveAccessMode )
	{
		std::cerr << "As yet this does not support export selected\nExporting all instead\n";
	}

	// open the output file
	//
	std::ofstream ofs(file.fullName().asChar());

	// make sure it opened ok
	if(!ofs) 
	{
		std::cerr << "[ERROR] Could not open file for writing " << file.fullName().asChar() << std::endl;
	}
	else 
	{
		// use an iterator to iterate through all nodes in the scene
		MItDependencyNodes it(MFn::kInvalid);

		// loop through all nodes
		for( ; !it.isDone(); it.next() )
		{
			// attach a function set to this node so we can access some data.
			// the dependency node is just one of many function set types we
			// can use, it forms the base class of all function sets used within the
			// maya API.
			MFnDependencyNode fn(it.item());

			// our only option is to see if we should output long or short names
			//
			if(m_bShort)
			{
				// just output the name of the node
				ofs << fn.name().asChar() << std::endl;
			}
			else 
			{
				// output a little info about this node
				ofs << "NODE:\t" << fn.name().asChar() << "\tTYPE:\tMFn::" << it.item().apiTypeStr() << std::endl;
			}
		}
		ofs.close();
	}
	return MS::kSuccess;
}


//-------------------------------------------------------------------	haveReadMethod
///	\brief  returns true if the file translator supports importing 
///	\return	false
///
bool  MayaFileTranslator::haveReadMethod	 () const {
	return false;
}


//-------------------------------------------------------------------	haveWriteMethod
///	\brief  returns true if the file translator supports exporting 
///	\return	true
///
bool MayaFileTranslator::haveWriteMethod	 () const {
	return true;
}


//-------------------------------------------------------------------	defaultExtension
///	\brief  returns the file extension of this format
///	\return	"rob"
///
MString MayaFileTranslator::defaultExtension () const {
	return "p3d";
}


//-------------------------------------------------------------------	identifyFile
///	\brief  This method is used to check to see if we support the 
///			specified file format. Usually it is sensible to have a 
///			standard identifier at the start of the file that you can
///			check, ie 'MYFILE01'. i don't have that luxury, so instead
///			I am using only a check against the files extension.
///	\param  fileName	-	the name of the file
///	\param	buffer		-	the first few bytes of the file
/// \param	size		-	number of bytes in buffer
///	\return	returns is my file type or is not my file type
///
MPxFileTranslator::MFileKind MayaFileTranslator::identifyFile(	const MFileObject& fileName,
						 const char* buffer,
						 short size) const {
	const char* str = fileName.name().asChar();
	unsigned int len = fileName.name().length();
	if (str[len-3] == 'p' &&
		str[len-2] == '3' &&
		str[len-1] == 'd')
	{
		return kCouldBeMyFileType;
	}
	return kNotMyFileType;
}

//-------------------------------------------------------------------	creator
///	\brief  Maya requires you to provide a static function that 
///			returns the address of a new instance of your node.
///	\return  new file translator node
///
void* MayaFileTranslator::creator() {
	return new MayaFileTranslator;
}





