# Toy Robot Code Challenge
## Description
This console application is a simulation of a toy robot moving on a square table top with dimensions of 5 units x 5 units.  

* There are no other obstructions on the table surface.
* The robot is free to roam around the surface of the table, but must be prevented from falling to destruction.
* Any movement that would result the robot falling from the table must be prevented, however further valid movement commands must still be allowed.

## Getting Started
### System Requirements

* C++ compiler that supports at least C++14
* CMake version 3.14 or higher

[CMake README](https://github.com/Kitware/CMake/blob/master/README.rst) is a helpful guide on how to get this system requirements setup on UNIX/Mac/Windows.

### Installation

1. Clone the repository.
    ```
    # Unix/Windows
    git clone https://github.com/mgemzon/toy-robot.git
    ```
2. Change directory to the cloned repository.
    ```
    # Unix/Windows
    cd toy-robot
    ```
3. Once in the toy-robot directory, generate the build files. Command below would create a new directory named `build` and all build related files will be placed there.
    ```
    # Unix/Windows
    cmake -S . -B build
    ```
4. After generating the build files, build the project.
    ```
    # Unix/Windows
    cmake --build build
    ```
5. After building the project, there should be two executable files in the `build` directory. The first executable is the application, the second executable is the unit test.  
    * Unix
        * build/toy_robot
        * build/toy_robot-Tests
    * Windows
        * build\toy_robot.exe
        * build\toy_robot-Tests.exe

### Running Application
Run the application executable.
```
# Unix
$ ./build/toy_robot
# Windows
> build\toy_robot.exe
```

Once the application is running, it waits for a input. The application recognizes these commands:
* `PLACE <x>,<y>,<direction>`
    * Places the robot on a specific location and direction on table.
    * `x` and `y` are any positive integer values. This is the x and y coordinate on where you want to place the robot on the table.
    * `direction` is the direction that the robot is facing. Possible values for these are:
        * `NORTH`
        * `EAST`
        * `WEST`
        * `SOUTH`
    * Example valid `PLACE` commands:
        * `PLACE 0,0,NORTH`
        * `PLACE 2,1,EAST`
        * `PLACE 1,3,WEST`
    * This command must be run first and must be placed in a valid location (within bounds of the table) before any other commands can be performed.

* `MOVE`
    * Moves the robot one unit forward it is currently facing.
* `LEFT`
    * Rotate the robot 90 degrees to the left.
* `RIGHT`
    * Rotate the robot 90 degrees to the right.
* `REPORT`
    * Reports the status of the robot.
    * Report has format `Output: <x>,<y>,<direction>`.
    * If robot is not placed yet, it won't report anything.

### Running Tests
1. Unit Tests

    Run the unit test executable.
    ```
    # Unix
    $ ./build/toy_robot-Tests

    # Windows
    > build\toy_robot-Tests.exe
    ```

After running the command above, it should output something like:
<details>  
  <summary>Click me</summary>

  ```
  [==========] Running 19 tests from 4 test suites.
  [----------] Global test environment set-up.
  [----------] 3 tests from TableTest
  [ RUN      ] TableTest.InvalidConstructorArguments
  [       OK ] TableTest.InvalidConstructorArguments (0 ms)
  [ RUN      ] TableTest.ValidLocations
  [       OK ] TableTest.ValidLocations (0 ms)
  [ RUN      ] TableTest.InvalidLocations
  [       OK ] TableTest.InvalidLocations (0 ms)
  [----------] 3 tests from TableTest (6 ms total)
  
  [----------] 9 tests from RobotTest
  [ RUN      ] RobotTest.PlaceRobotOnValidTableLocations
  [       OK ] RobotTest.PlaceRobotOnValidTableLocations (0 ms)
  [ RUN      ] RobotTest.PlaceRobotOnInvalidLocations
  [       OK ] RobotTest.PlaceRobotOnInvalidLocations (0 ms)
  [ RUN      ] RobotTest.RotateLeft
  [       OK ] RobotTest.RotateLeft (0 ms)
  [ RUN      ] RobotTest.RotateRight
  [       OK ] RobotTest.RotateRight (0 ms)
  [ RUN      ] RobotTest.UnplacedRobotAndPerformMove
  [       OK ] RobotTest.UnplacedRobotAndPerformMove (0 ms)
  [ RUN      ] RobotTest.UnplacedRobotAndPerformLeft
  [       OK ] RobotTest.UnplacedRobotAndPerformLeft (0 ms)
  [ RUN      ] RobotTest.UnplacedRobotAndPerformRight
  [       OK ] RobotTest.UnplacedRobotAndPerformRight (0 ms)
  [ RUN      ] RobotTest.UnplacedRobotAndPerformReport
  [       OK ] RobotTest.UnplacedRobotAndPerformReport (0 ms)
  [ RUN      ] RobotTest.PlaceRobotAndMoveAtTableEdge
  [       OK ] RobotTest.PlaceRobotAndMoveAtTableEdge (0 ms)
  [----------] 9 tests from RobotTest (18 ms total)
  
  [----------] 6 tests from ControllerTest
  [ RUN      ] ControllerTest.PassingValidPlaceCommands
  [       OK ] ControllerTest.PassingValidPlaceCommands (1 ms)
  [ RUN      ] ControllerTest.PassingValidMoveCommands
  [       OK ] ControllerTest.PassingValidMoveCommands (0 ms)
  [ RUN      ] ControllerTest.PassingValidLeftCommands
  [       OK ] ControllerTest.PassingValidLeftCommands (0 ms)
  [ RUN      ] ControllerTest.PassingValidRightCommands
  [       OK ] ControllerTest.PassingValidRightCommands (0 ms)
  [ RUN      ] ControllerTest.PassingValidReportCommands
  [       OK ] ControllerTest.PassingValidReportCommands (0 ms)
  [ RUN      ] ControllerTest.PassingInvalidCommands
  [       OK ] ControllerTest.PassingInvalidCommands (0 ms)
  [----------] 6 tests from ControllerTest (14 ms total)
  
  [----------] 1 test from ControllerConstructorTest
  [ RUN      ] ControllerConstructorTest.InvalidArguments
  [       OK ] ControllerConstructorTest.InvalidArguments (0 ms)
  [----------] 1 test from ControllerConstructorTest (2 ms total)
  
  [----------] Global test environment tear-down
  [==========] 19 tests from 4 test suites ran. (51 ms total)
  [  PASSED  ] 19 tests.
  ```

</details>

The output above is the report of the unit test. The unit test is created using GoogleTest.

2. Application Test

    This tests the application as a whole by running the application with defined inputs, and we compare its output with an expected output. 

    In the `application_test` folder it has a file named `input_commands.txt`, this is the defined inputs that we pass to the application. The file named `expected_output.txt` is the expected output of the application with the given inputs.

    ```
    # Creates an output.txt file that stores the output of the application
    # after supplying it with defined input commands.

    # Unix
    $ ./build/toy_robot < application_test/input_commands.txt > application_test/output.txt

    # Windows
    > build\toy_robot.exe < application_test\input_commands.txt > application_test\output.txt
    ```

    After the application is ran with the defined inputs, `application_test/output.txt` and `application_test/expected_output.txt` is compared. Both files should be the same to signify that the application is working properly.

    ```
    # Comparing exected_output.txt and output.txt

    # Unix
    $ diff application_test/output.txt application_test/expected_output.txt
    $ echo $?           # Echo exit return code of previous command
    0                 # 0 exit status means files are the same, 1 if files are not the same.

    # Windows
    > fc application_test\output.txt application_test\expected_output.txt
    FC: no differences encountered
    > echo %ERRORLEVEL%
    0                 # 0 exit status means files are the same, 1 if files are not the same.
    ```
