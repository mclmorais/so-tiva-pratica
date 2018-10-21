## Output pingpong-scheduler (P4):

```
----------Inicializacao completa----------
main: inicio
    Pang: inicio (prioridade 0)
    Pang: 0
    Pang: 1
    Pang: 2
        Peng: inicio (prioridade 2)
        Peng: 0
    Pang: 3
    Pang: 4
            Ping: inicio (prioridade 4)
            Ping: 0
    Pang: 5
        Peng: 1
    Pang: 6
                Pong: inicio (prioridade 6)
                Pong: 0
    Pang: 7
                    Pung: inicio (prioridade 8)
                    Pung: 0
    Pang: 8
        Peng: 2
    Pang: 9
            Ping: 1
    Pang: fim
        Peng: 3
                Pong: 1
        Peng: 4
        Peng: 5
            Ping: 2
        Peng: 6
                    Pung: 1
        Peng: 7
        Peng: 8
            Ping: 3
        Peng: 9
                Pong: 2
        Peng: fim
            Ping: 4
                    Pung: 2
            Ping: 5
            Ping: 6
                Pong: 3
            Ping: 7
            Ping: 8
            Ping: 9
                Pong: 4
            Ping: fim
                Pong: 5
                    Pung: 3
                Pong: 6
                Pong: 7
                Pong: 8
                    Pung: 4
                Pong: 9
                Pong: fim
                    Pung: 5
                    Pung: 6
                    Pung: 7
                    Pung: 8
                    Pung: 9
                    Pung: fim
main: fim
----------Termino: loop infinito----------
```