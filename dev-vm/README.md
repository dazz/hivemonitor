# Virtual Machine

Development environment for hive monitor.

```bash
dev-vm
├── README.md
├── roles
│   ├── common           # vim, zsh, ...
│   ├── couchdb          # TODO. no-sql database to store the data for deeper analysis
│   ├── grafana          # Display monitoring dashboards
│   ├── influxdb         # Timeseries database
│   ├── mosquitto        # MQTT message bus server
│   └── supervisor       # watcher to (re-)start scripts and services
├── site.yml             # 2. Definition of software to be installed
├── vagrant.box.ubuntu
├── Vagrantfile          # 1. Definition of the VM
└── vars
    └── all.yml          # config
```

### TOC

1. Prerequisites
1. Install
1. Run

## Prerequisites

Install Vagrant to load and manage a virtual machine.

```bash
sudo apt-get install vagrant 
```

Install Ansible to provision the machine and create development environment.

```bash
sudo apt-get install ansible
```

## Install

```bash
git clone https://github.com/hivemonitor/dev-vm hivemonitor/dev-vm
cd hivemonitor/dev-vm
vagrant up --provision
```

The following things are expected to happen:
* base image gets downloaded
* VM boots
* ansible provisions the VM

When all is done try `vagrant ssh`.

## still TODO

* [x] install Mosquito
* [ ] install CouchDB
* [ ] add a template for bash aliases
* [ ] direct all logs to /var/log/syslog

## Credits

* https://github.com/zenoamaro/ansible-supervisord.git
* https://github.com/guillaumededrie/ansible-role-couchdb