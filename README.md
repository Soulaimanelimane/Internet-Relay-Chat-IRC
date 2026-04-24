_This project has been created as part of the 42 curriculum by slimane | bbenaali | omaezzem_


# ft_irc

## Description

This project is about creating a simple **IRC server** in C++.

The server allows multiple clients to connect, authenticate, join channels, and send messages. It works using TCP/IP and handles multiple clients at the same time using non-blocking I/O.

The main goal is to understand how networking and real-time communication work.

---

## Instructions

### Compile

```bash
make
```

### Run

```bash
./ircserv <port> <password>
```
```bash
client side :
nc -c (localhost or the ip of the server) <port>
```


### Usage

Connect using an IRC client (like irssi or weechat), then:

* login
* set nickname
* join a channel
* send messages

---

## Resources

* our peers  
* https://modern.ircdocs.horse/
* ft_irc subject
* AI especilly for detailed concepts

---

## usage examples

```bash
server side :
./ircserv 2005 password
```

```bash
client side :
nc -c localhost 2005  # to connect  with the server
pass password # the password of the server to be authenticate to joi channels and talk with other server's user
NICK soulaimane # set your nickname is mandatory to set it 
USER slimane 0 * : limane # set your username and your realname also this step is mandatory
BOT CMD # to show you all the command you use in our server 

```
**real example in terminal**
![Alt text](/mnt/homes/slimane/Desktop/Screen Shot 2026-04-18 at 7.27.31 PM.png)