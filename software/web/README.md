# Briefcase Web Application
Frontend for managing Briefcase
## Authors
1. [**Samuel Obosu**]

## Tools
1. Programming Language - [Python3](https://www.python.org)
2. Framework - [Flask](http://flask.pocoo.org/) v1.0.2

## Building the project

This is a [Python3](https://www.python.org) based in the [Flask](http://flask.pocoo.org) framework, so ensure python is install on the machine.
You can check if python is installed on the machine by typing the command
```
python
```
from the terminal or command prompt.

Read about how to install Python3 from https://www.python.org/downloads/

Change to the project directory and run from the terminal
```
pip install -r requirements.txt
```
This will install all the project dependencies. The dependencies are listed in the requirements file.

## Running the application
From the terminal, run the command
```
uwsgi --ini application.ini --gevent [number_of_event_loop_needded]
```
uwsgi[https://uwsgi-docs.readthedocs.io/] provides various protocols for running python scripts and for scaling traffic.

### Running Test
1. From the terminal, change to the root of the project directory
2. Run the command below which runs all test
```
behave tests
```

# Recommendations

# TODOS
