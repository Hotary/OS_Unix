FROM python:latest
ENV SRC_DIR /usr/bin/webapps/HelloUnix
COPY src/* ${SRC_DIR}/
WORKDIR ${SRC_DIR}
ENV PYTHONUNBUFFERED=1
RUN apt-get update -y
RUN apt-get install -y python3-pip python-dev build-essential
RUN pip3 install Flask
CMD ["python", "main.py"]
