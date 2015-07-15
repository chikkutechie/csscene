
test_Executables = \
					utest_matrix \
                    utest_transformation

bin_PROGRAMS = $(test_Executables)

utest_matrix_SOURCES = ../utest_matrix.cpp
utest_transformation_SOURCES = ../utest_transformation.cpp

INCLUDES = -I../../external/bullet/src -I../../inc \
           -I../../inc/bullet  -I../../inc/core -I../../inc/gc  -I../../inc/glut  -I../../inc/math  -I../../inc/scene -I../../inc/x11
LIBS = \
       -L../../external/bullet/linux -lbullet \
       -L../../external/tinyxml/linux -ltinyxml \
       -L../../external/lodepng/linux -llodepng \
       -L../../linux -lchikkooos \
       -lGL -lGLU -lglut -lEGL
       
CXXFLAGS = -g3 -Wall -DGL_GLEXT_PROTOTYPES
CFLAGS = -g3 -Wall
LDFLAGS = -g3

test: $(test_Executables)

run: test
	allpass=1;\
	for v in $(test_Executables); do \
		echo ; \
		echo -e "\x1b[34;01m" "RUNNING "$$v; \
		echo -e "\x1b[39;49;00m"; \
		./$$v; \
		if [ $$? -ne 0 ]; \
		then \
			echo -e "\x1b[34;01m" "\t\t**************************************************"; \
			echo -e "\x1b[34;01m" "\t\t\tFAILED : ["$$v]; \
			echo -e "\x1b[34;01m" "\t\t**************************************************"; \
			echo -e "\x1b[39;49;00m"; \
			allpass=0; \
			break; \
		fi \
	done \
	; \
	if [ $$allpass -eq 1 ]; \
	then \
		echo -e "\x1b[34;01m" "\t\t**************************************************"; \
		echo -e "\x1b[34;01m" "\t\t               ALL THE TEST CASES PASSED"; \
		echo -e "\x1b[34;01m" "\t\t**************************************************"; \
		echo -e "\x1b[39;49;00m"; \
	fi
