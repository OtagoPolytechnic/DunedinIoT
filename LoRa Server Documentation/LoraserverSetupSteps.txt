# Run <code>cat /etc/*-release</code> and copy the DISTRIB_ID and DISTRIB_CODENAME values.

# Install the LoRa Server Debian repository. Replace DISTRIB_ID and DISTRIB_CODENAME with the values copied earlier.
```
source /etc/lsb-release
sudo apt-key adv --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys 1CE2AFD36DBCCA00 # (thanks Brendan: https://community.spotify.com/t5/Desktop-Linux-Windows-Web-Player/Can-t-install-public-key/td-p/91153)
sudo echo "deb https://repos.loraserver.io/${DISTRIB_ID,,} ${DISTRIB_CODENAME} testing" | sudo tee /etc/apt/sources.list.d/loraserver.list
```

# Install MQTT broker
```
sudo apt-add-repository ppa:mosquitto-dev/mosquitto-ppa
sudo apt-get update
sudo apt-get install mosquitto
```

# Install LoRa Gateway Brige 
```
sudo apt-get install lora-gateway-bridge
```

# Add the loraserver repository to source update list
```
sudo echo "deb https://repos.loraserver.io/ubuntu xenial testing" | sudo tee /etc/apt/sources.list.d/loraserver.list
sudo apt-get update
```

# Install redis-server
```
sudo apt-get install redis-server
```

# Install PostgreSQL
```
wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
sudo echo "deb http://apt.postgresql.org/pub/repos/apt/ xenial-pgdg main" | sudo tee /etc/apt/sources.list.d/pgdg.list
sudo apt-get update
sudo apt-get install postgresql-9.6
```

# Creating a user and database for loraserver. Choose your own secure password. Remember the role and password for later.
```
sudo -u postgres psql
create role loraserver_ns with login password '********';
create database loraserver_ns with owner loraserver_ns;
\q
```

# Install LoRaServer
```
sudo apt-get install loraserver
```

# Change settings in /etc/default/loraserver:
## Change NET_ID to your own 3 byte value (eg 010203)
## Change BAND to AU_915_928 (which is the legal bandwidth allowed in New Zealand)
## Change user:password@hostname in POSTGRES_DSN to the role and password you used in the PostgreSQL loreaserver database. Change 'hostname' to 'localhost'.
## Change TIMEZONE to Pacifica/Auckland (or whichever timezone you are in)
## Save changes and exit

# Install lora-app-server
```
sudo apt-get install lora-app-server
```

# Create a user and database for lora-app-server. Remember the role and password for later.
sudo -u postgres psql
create role loraserver_as with login password '********';
create database loraserver_as with owner loraserver_as;
\q
sudo apt-get install lora-app-server

# Run <code>openssl rand -base64 32</code> and copy the output.
# Change settings in /etc/default/lora-app-server:
## Change user:password@hostname in POSTGRES_DSN to the role and password you used in the PostgreSQL lora-app-server database. Change 'hostname' to 'localhost'. 
## Change JWT_TOKEN to the copied output of the openssl command
## Save changes and exit

To run the server:
```
sudo systemctl start lora-gateway-bridge
sudo systemctl start loraserver
sudo systemctl start lora-app-server
```
go to web browser and navigate to https://localhost:8080
