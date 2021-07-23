
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


### Example scenario

1. HR wants to build a new job: <br />

$ ./run_in_docker.sh new-job Software Developer <br />

2. First candidate applies: <br />

$ ./run_in_docker.sh new-candidate Anna Hack <br />
$ ./run_in_docker.sh apply Anna Hack for Software Developer <br />

3. Second candidate applies: <br />

$ ./run_in_docker.sh new-candidate Jimmy Page <br />
$ ./run_in_docker.sh apply Jimmy Page for Software Developer <br />

4. Third candidate applies: <br />

$ ./run_in_docker.sh new-candidate Joe Doe <br />
$ ./run_in_docker.sh apply Joe Doe for Software Developer <br />

5. Second candidate is immediately rejected, does not have requested education: <br />

$ ./run_in_docker.sh reject Jimmy Page for Software Developer <br />

6. In the meantime another job offer comes up: <br />

$ ./run_in_docker.sh new-job Data Scientist <br />

7. First candidate is interviewed for 1st job: <br />

$ ./run_in_docker.sh interviewed Anna Hack for Software Developer <br />

8. Third candidate is interviewed for 1st job: <br />

$ ./run_in_docker.sh interviewed Joe Doe for Software Developer <br />

9. Third candidate is rejected, first candidate gets the job: <br />

$ ./run_in_docker.sh reject Joe Doe for Software Developer <br />
$ ./run_in_docker.sh accept Anna Hack for Software Developer <br />

10. Fourth candidate applies to the second job: <br />

$ ./run_in_docker.sh new-candidate Sophia Calanthe <br />
$ ./run_in_docker.sh apply Sophia Calanthe for Data Scientist <br />

11. Fourth candidate is accepted: <br />

$ ./run_in_docker.sh accept Sophia Calanthe for Data Scientist <br />

Remember, you can always print the status of the database running: <br />

$ ./run_in_docker.sh show-all <br />

Also remeber, you can always use index of job / candidate instead od position name / name, using @. <br />
e.g for step 7: <br />
$ ./run_in_docker.sh interviewed @0 for @0 <br />


Please note: the app stores a local file `db` with data about jobs and candidates.


### Running
The largest `todo` are automatic tests.
I tested this manually, but it was only 48h, so I did not have time to prepare proper automated tests.

