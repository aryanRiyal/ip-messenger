FROM gcc:12
WORKDIR /app

# Copy lib and client source code
COPY lib/ ./lib/
COPY client/ ./client/

# Build the client
WORKDIR /app/client
RUN make

# Entrypoint specifies runC, user will pass arguments when running
ENTRYPOINT ["./runC"]
