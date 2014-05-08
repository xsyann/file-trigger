#!/usr/bin/env python
##
## server.py
##
## Made by xsyann
## Contact <contact@xsyann.com>
##
## Started on  Thu May  8 12:10:57 2014 xsyann
## Last update Thu May  8 13:14:07 2014 xsyann
##

"""
File Trigger server.

Authors: Nicolas de Thore, Yann Koeth
"""

import socket
import threading

class ClientThread(threading.Thread):

    def __init__(self, ip, port, socket):
        threading.Thread.__init__(self)
        self.ip = ip
        self.port = port
        self.socket = socket
        print "Thread for {}:{}".format(ip, port)

    def run(self):
        self.socket.send("Welcome\n")

class FileTriggerServer:

    def __init__(self, host, port):

        self.socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

        self.socket.bind((host, port))
        print "Running... {}:{}".format(host, port)
        self.threads = []

    def cleanup(self):
        for thread in self.threads:
            thread.join()

    def run(self):
        while True:
            try:
                self.socket.listen(4)
                (client, (ip, port)) = self.socket.accept()
                thread = ClientThread(ip, port, client)
                thread.start()
                self.threads.append(thread)
            except KeyboardInterrupt:
                print "Bye."
                break
        self.cleanup()

if __name__ == "__main__":
    import argparse, sys

    default = {'l': "192.168.0.3",
               'p': 12345,
               's': "/tmp/storage"}

    parser = argparse.ArgumentParser(description="File Trigger server.")
    parser.add_argument("-l", "--location", type=str,
                        help="Host", default=default['l'])
    parser.add_argument("-p", "--port", type=int,
                        help= "Port", default=default['p'])
    parser.add_argument("-s", "--storage", type=str,
                        help="Storage path", default=default['s'])
    args = parser.parse_args()

    print __doc__

    fts = FileTriggerServer(args.location, args.port)
    fts.run()


