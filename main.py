import socket
import threading

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((socket.gethostbyname(socket.gethostname()), 6060))
server.listen(5)
print(socket.gethostbyname(socket.gethostname()))


def clt_thread(client, addr):
    
    is_connected = True
    while is_connected:
        message = client.recv(1024).decode('utf-8')
        print(message)

        client.send(bytes("hello from the server", 'utf-8'))

        if str(message).startswith('disconnected'):
            is_connected = False
            break

    client.close()


while True:
    print('waiting')
    clt, addr = server.accept()
    print('connection')

    thread = threading.Thread(target=clt_thread, args=(clt, addr))
    thread.start()
