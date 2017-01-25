# Server Mechanic [![Build Status](https://travis-ci.org/server-mechanic/mechanic.svg)](https://travis-ci.org/server-mechanic/mechanic) [![Release](https://img.shields.io/github/release/server-mechanic/mechanic.svg)](https://github.com/server-mechanic/mechanic/releases/latest) [![License](https://img.shields.io/badge/License-Apache%202.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)

### Server Evolution Made Easy.

![Server Mechanic](https://server-mechanic.github.io/website/images/mechanic_small.png "Server Mechanic")

#### Evolve your containers and virtual machines more easily.

## Features

### Pros
* Evolve your servers step by step.
* Write server migrations in your favorite language.
* Use the standard tools developed for the job, e.g. apt, yum, dnf.
* Focus on the migrations instead of developing reusable plugins.
* Minimal overhead, no central server required.

### Cons
* List of migrations can get very long for new installs.

## What Server Mechanic is for?
If you want to manage your machines in a traceable and repeatable way one strategy is the creation of "infrastructure as code".

With Server Mechanic you author changes to your machines as scripts in your favorite language, e.g. shell scripts. Server Mechanic collects these migration scripts, executes them and records them as applied in an internal database. Next time only new migrations will be executed. In case of an error you fix the problem and start over.

Server Mechanic is considered a lightweight alternative to tools like puppet, ansible, etc.

## Server Mechanic for Docker containers

Docker already utilizes the step by step approach with the commands in your Dockerfile. These commands are run at container image build time. So you have full access to the container's internal state. But external volumes injected into a container instance cannot be manipulated by Dockerfile commands. Here Server Mechanic comes into play.

Server Mechanic gets executed on container startup, applies your migration which migrates the state in your volumes, then container startup proceeds. So you can roll out adjustments to external volumes with new container versions and containers and volumes stay in sync.

## Status

Server Mechanic is in an early stage ("unstable"). Use it carefully and expect things to break.

We appreciate any feedback about the tool and your usage scenarios so we can learn and improve Server Mechanic.

## Installation

### Bare metal/ virtual machines
* Install mechanic
```
curl -s https://raw.githubusercontent.com/server-mechanic/packages/master/install-mechanic.sh | sudo bash -s unstable
```
* Place your migrations below /var/lib/mechanic/migration.d/ or /etc/mechanic/migration.d/. (Make sure they are executable and exit with 0 in case of success.)
* Start the Server Mechanic
```
mechanic migrate
```

### Docker container
* Add installation of mechanic to your Dockerfile
```
RUN curl -s https://raw.githubusercontent.com/server-mechanic/packages/master/install-mechanic.sh | sudo bash -s unstable
```
* Supposedly you want mechanic state to survice container restarts, so add a volume:
```
VOLUME /mechanic.volume
```
* Adjust /etc/mechanic.conf so mechanic will put state into the volume:
```
# /etc/mechanic.conf
[main]
log_file=/mechanic.volume/log/mechanic.log
migration_dirs=/var/lib/mechanic/migration.d/
run_dir=/mechanic.volume/tmp/
state_dir=/mechanic.volume/state
```
* Place your migrations below /var/lib/mechanic/migration.d/. (Make sure they are executable and exit with 0 in case of success.)
* Extend your container entrypoint so, that mechanic migrations will be run on container startup. Mechanic will replace itself with the actual endpoint.
```
ENTRYPOINT ["/usr/sbin/mechanic", "migrate", "--", "PUT", "ACTUAL", "ENTRYPOINT", "HERE" ]
```
* Don't forget to start your container with the external volume mounted. (-v /path/to/volume:/mechanic.volume).

## History

[History](HISTORY.md)

## Contributing

Server Mechanic is an open source project, and contributions are welcome! Feel free to raise an issue or submit a pull request.

## License
Copyright (c) 2016 by the [Server Mechanic Team](https://github.com/orgs/server-mechanic/people).

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

[http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

## Trademark hints
Docker is a trademark or registered trademark of Docker, Inc.; Puppet is a trademark or registered trademark of Puppet, Inc.; Ansible is a trademark or registered trademark of Red Hat, Inc.
