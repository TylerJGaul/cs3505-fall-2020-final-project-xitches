# ubuntu based system
FROM ubuntu


# Set a default shell.
SHELL ["/bin/bash", "-c"]

# The timezone library stops the docker build and waits for user input to
# select a timezone. This breaks the build. To get around this, 
# set up timezone information prior to installing that library. This
# Docker code does that. Composited from two sources:
# https://rtfm.co.ua/en/docker-configure-tzdata-and-timezone-during-build/
# https://serverfault.com/questions/949991/how-to-install-tzdata-on-a-ubuntu-docker-image

ARG DEBIAN_FRONTEND=noninteractive
ENV TZ="America/Salt Lake City"

# Install a handful of useful libraries.  Note that this is generally against
# best practices -- containers should be lean, and not include 'things you
# might use'.  In our case, we're using the containers for development, so
# this may be reasonable here.

RUN apt-get -y update && apt-get -y install \
   apt-utils \
   python3 \
   python3-pip \
   curl \
   unzip
   
RUN curl "https://awscli.amazonaws.com/awscli-exe-linux-x86_64.zip" -o "awscliv2.zip" && \
unzip awscliv2.zip && \
./aws/install


   
RUN pip3 install finnhub-python \
boto3 \
requests
   
RUN mkdir cs3505

# Copy in the files from the current folder (recursively) For our purposes
# put them in /python

COPY . /python

# Execute scraper to get COVID cases

CMD python3 python/COVIDWebscrape.py