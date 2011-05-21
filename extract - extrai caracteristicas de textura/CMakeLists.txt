cmake_minimum_required(VERSION 2.4)

PROJECT(extract)

FIND_PACKAGE ( ITK)
IF ( ITK_FOUND)
	INCLUDE( ${USE_ITK_FILE} )
ENDIF( ITK_FOUND)


ADD_EXECUTABLE(extract
	main.cpp
	RGBFilter.cpp)

TARGET_LINK_LIBRARIES (extract
	ITKBasicFilters
	ITKCommon
	ITKStatistics
	ITKIO
	ITKNumerics
)
