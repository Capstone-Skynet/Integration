# Camera Test using Python

This is a complementary program that uses Python to feed images to the skynet web app. 

## Requirements

- Python 3.7+
- pipenv

## Setup

If you already have `pipenv`, skip to the [next section](#packages).

### Pipenv

First, make sure we have `pipenv`, the package manager for Python installed as we need a few Python packages:

```shell
pip install --user pipenv
```

Make sure to add `--user` so that we don't mess with the system's Python libraries. However, this also means that we need to add the user directory to environment path so that we can use `pipenv` command. The user base directory can be found by using this command:

```shell
python -m site --user-base
```

This might look something like `/Users/muchenhe/Library/Python/3.7`. Then add that to `PATH`:

```shell
export PATH=$HOME/Library/Python/3.7/bin:$PATH
```

Ensure that `pipenv` is accessible by checking its version:

```shell
pipenv --version
```

### Packages

Run the following command and the dependencies should automatically install:

```shell
pipenv install
```

## Usage

The entry point to the camera test program is `client.py`. We can launch it by using *either* one of the following commands:

```shell
pipenv shell

python client.py
```

or

```shell
pipenv run python client.py
```