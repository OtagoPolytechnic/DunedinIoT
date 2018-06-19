Installing CA certificates, from `https://letsencrypt.org/getting-started/`:  
`We recommend that most people with shell access use the Certbot ACME client.`  
from `https://certbot.eff.org/#ubuntuxenial-other`:  
```
$ sudo apt-get update
$ sudo apt-get install software-properties-common
$ sudo add-apt-repository ppa:certbot/certbot
$ sudo apt-get update
$ sudo apt-get install certbot 
```
`If you already have a webserver running, we recommend choosing the "webroot" plugin. To obtain a cert using the "webroot" plugin, which can work with the webroot directory of any webserver software:`  
from `https://www.digitalocean.com/community/tutorials/how-to-use-certbot-standalone-mode-to-retrieve-let-s-encrypt-ssl-certificates`

```
dunedinadmin@ubuntu:/etc/lora-app-server/certs$ sudo certbot certonly --standalone --preferred-challenges tls-sni -d iot.op-bit.nz
Saving debug log to /var/log/letsencrypt/letsencrypt.log
Enter email address (used for urgent renewal and security notices) (Enter 'c' to
cancel): macdo5@student.op.ac.nz

-------------------------------------------------------------------------------
Please read the Terms of Service at
https://letsencrypt.org/documents/LE-SA-v1.1.1-August-1-2016.pdf. You must agree
in order to register with the ACME server at
https://acme-v01.api.letsencrypt.org/directory
-------------------------------------------------------------------------------
(A)gree/(C)ancel: A

-------------------------------------------------------------------------------
Would you be willing to share your email address with the Electronic Frontier
Foundation, a founding partner of the Let's Encrypt project and the non-profit
organization that develops Certbot? We'd like to send you email about EFF and
our work to encrypt the web, protect its users and defend digital rights.
-------------------------------------------------------------------------------
(Y)es/(N)o: N
Obtaining a new certificate
Performing the following challenges:
tls-sni-01 challenge for iot.op-bit.nz
Waiting for verification...
Cleaning up challenges

IMPORTANT NOTES:
 - Congratulations! Your certificate and chain have been saved at:
   /etc/letsencrypt/live/iot.op-bit.nz/fullchain.pem
   Your key file has been saved at:
   /etc/letsencrypt/live/iot.op-bit.nz/privkey.pem
   Your cert will expire on 2017-12-17. To obtain a new or tweaked
   version of this certificate in the future, simply run certbot
   again. To non-interactively renew *all* of your certificates, run
   "certbot renew"
 - Your account credentials have been saved in your Certbot
   configuration directory at /etc/letsencrypt. You should make a
   secure backup of this folder now. This configuration directory will
   also contain certificates and private keys obtained by Certbot so
   making regular backups of this folder is ideal.
 - If you like Certbot, please consider supporting our work by:

   Donating to ISRG / Let's Encrypt:   https://letsencrypt.org/donate
   Donating to EFF:                    https://eff.org/donate-le
```
Edit the HTTP_TLS_CERT variable to /etc/letsencrypt/live/iot.op-bit.nz/fullchain.pem and HTTP_TLS_KEY to /etc/letsencrypt/live/iot.op-bit.nz/privkey.pem
`crontab -e`
`0 02 01 */3 * certbot renew`
Will run every three months at 03:30 on the 1st of Jan,Apr,Jul and Oct.

Add the group `cacert` to manage certificates
```
sudo groupadd cacert
sudo usermod dunedinadmin -aG cacert
cd /etc/letsencrypt
sudo chgrp -R cacert live
sudo chgrp cacert live
sudo chmod -R 774 live
``` 