
### Overview
This repo implements my solution to HR system coding challenge.


### Building Docker image
I recommend running everything inside a Docker container.
To build the Docker image run:

$ ./build_docker.sh

This will build Docker image `jacek_solution_build`.
It takes around a minute to build the image on my laptop.

### C++ version
I use C++17, this is why gcc at least 9.1 is required.


### Compilation
To compile the system run:

$ ./build_in_docker.sh

This will build `hrsystem` in the current directory.


### Running

Get help
------------------------
To see the help run:

$ ./run_in_docker.sh help

It will print all the possible commands.


Example scenario
------------------------
1. HR wants to build a new job:

$ ./run_in_docker.sh new-job Software Developer


2. First candidate applies

$ ./run_in_docker.sh new-candidate Anna Hack
$ ./run_in_docker.sh apply Anna Hack for Software Developer

3. Second candidate applies

$ ./run_in_docker.sh new-candidate Jimmy Page
$ ./run_in_docker.sh apply Jimmy Page for Software Developer

4. Third candidate applies

$ ./run_in_docker.sh new-candidate Joe Doe
$ ./run_in_docker.sh apply Joe Doe for Software Developer

5. Second candidate it immediately rejected, does not have requested education.

$ ./run_in_docker.sh reject Jimmy Page for Software Developer

6. In the meantime another job offer comes up

$ ./run_in_docker.sh new-job Data Scientist

7. First candidate is interviewed for 1st job

$ ./run_in_docker.sh interviewed Anna Hack for Software Developer

8. Third candidate is interviewed for 1st job

$ ./run_in_docker.sh interviewed Joe Doe for Software Developer

9. Third candidate is rejected, first candidate gets the job

$ ./run_in_docker.sh reject Joe Doe for Software Developer
$ ./run_in_docker.sh accept Anna Hack for Software Developer

10. Fourth candidate applies to the second job

$ ./run_in_docker.sh new-candidate Sophia Calanthe
$ ./run_in_docker.sh apply Sophia Calanthe for Data Scientist

11. Fourth candidate is accepted.

$ ./run_in_docker.sh accept Sophia Calanthe for Data Scientist

Remember, you can always print the status of the database running:

$ ./run_in_docker.sh show-all

Also remeber, you can always use index of job / candidata instead od position name / name, using @.
E.G for step 7:
$ ./run_in_docker.sh interviewed @0 for @0


Please note: the app stores a local file `db` with data about jobs and candidates.


### Running
The largest `todo` are automatic tests.
I tested this manually, but it was only 48h, so I did not have time to prepare proper automated tests.

