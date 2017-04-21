Semester Project, Second Deliverable.
Due: 4/23/17

Authors (initials):
    Asadullah Khan  (AK)
    James Anserson (JA)
    Salman Anwer (SA)
    Tiffany Do (TD)
    Seong Ioi Wang (SW)
    Dylan Yu (DY)
    
Files in zip: echo_c.c, echo_c_udp.c, client_functions.c, client_functions.h, echo_s.c, server_functions.c, server_functions.h, echo.log, Makefile and readme.txt

Purpose:
    create a "echo_s" executable that accepts TCP/UDP messages and a "echo_c" executable that sends messages to a port(server). The server (echo_s) should then reply to the client with the same message it receives.
    echo_c.c is used to send TCP messages and echo_udp.c is used to send UDP messages.
    echo_s will then forward a record of the messages it receives to the "log_s" server. log_s will then log this information in a log file "echo.log" 
    
Description:
    extract files and run makefile dumby