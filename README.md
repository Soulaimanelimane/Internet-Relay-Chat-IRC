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
BOT CMD # to show you all the command you use in our server --this is for bonus--

```


## Bonus part 

# file transfer :
    * in this part we should learn how the file is transferred in IRC server .
    * the irc servers use the DCC that is a sub-protocol enabling peers to interconnect using an IRC server for handshaking in order to exchange files or perform non-relayed chats.
    * to perfom this we use this command :
```bash
    # terminal 1 :
        nc -l 9000 < filename or cat filename | nc -l 9000
    # terminal 2 :
    {
        echo  "PASS soul"
        echo  "NICK sender"
        echo  "USER sender 0 * :sender"
        sleep 2
        echo -e "PRIVMSG bbenaali :\001DCC SEND Makefile 2130706433 9000 505\001\r"
    } | nc -c localhost 2005
```
    that create a new client who will send to the client in limechat named bbenaali(before running the command u should create a client in limechat)
    - and with that the file will be transferred

# BOT :
```bash
#  just run 
    BOT HELP
```
* and it will gives you all the command the bot uses .
