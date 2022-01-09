import init
import time
import smtplib, ssl

myparms = init.get_parms()
port = 465  # For SSL
smtp_server = "smtp.gmail.com"
sender_email = "servicewin44@gmail.com"
receiver_email = myparms[1]
password = "ali2001meknes"
message = """\
Subject: Felicitations

Vous avez gagne un marche. Merci de consulter votre compte sur l'application RIA."""

context = ssl.create_default_context()
with smtplib.SMTP_SSL(smtp_server, port, context=context) as server:
    server.login(sender_email, password)
    server.sendmail(sender_email, receiver_email, message)
