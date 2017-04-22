Semester Project, Second Deliverable
Due: 4/23/17

Authors (initials):
    Asadullah Khan  (AK)
    James Anserson (JA)
    Salman Anwer (SA)
    Tiffany Do (TD)
    Seong Ioi Wang (SW)
    Dylan Yu (DY)
    
Files in zip: echo_c.c, client_functions.c, echo_s.c, server_functions.c, echo.log, Makefile and readme.txt

Purpose:
    Create a "echo_s" executable that accepts TCP/UDP messages and a "echo_c" executable that sends messages to a port(server). The server (echo_s) should then reply to the client with the same message it receives.
    echo_c is able to send messages using TCP or UDP based on the option passed to it.
    echo_s will then forward a record of the messages it receives to the "log_s" server. log_s will then log this information in a log file "echo.log" 
    
Description:
    extract files and run makefile dumby