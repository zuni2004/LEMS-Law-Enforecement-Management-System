all: ./a.out

compRun:
	g++ -std=c++11 *.cpp -o r.out
#	g++ -std=c++11 main.cpp User.cpp AdministrativeStaff.cpp ASI.cpp SI.cpp IP.cpp officer.cpp Citizen.cpp HR.cpp HR2.cpp Budget.cpp Investigation.cpp Crime.cpp Bail.cpp Cells.cpp CorrectionalOfficer.cpp Criminal.cpp Evidence.cpp -o r.out

compTest:
	g++ -std=c++11  *.cpp -o a.out

test: clean compTest; ./a.out

run: clean compRun; ./r.out
clean:
	rm -f *.out
