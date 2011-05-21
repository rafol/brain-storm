cmake_minimum_required(VERSION 2.4)

PROJECT(ContaGotas)

FIND_PACKAGE ( ITK)
IF ( ITK_FOUND)
	INCLUDE( ${USE_ITK_FILE} )
ENDIF( ITK_FOUND)


ADD_EXECUTABLE(contaGotas
	MaskGenerator.cpp
	RGBFilter.cpp
	BlobExtractor.cpp
	contaGotas.cpp)

TARGET_LINK_LIBRARIES (contaGotas
	ITKBasicFilters
	ITKCommon
	ITKStatistics
	ITKIO
	ITKNumerics
)
