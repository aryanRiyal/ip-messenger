FROM gcc:12
WORKDIR /app

# Copy lib and server source code
COPY lib/ ./lib/
COPY server/ ./server/

# Build the server
WORKDIR /app/server
RUN make

EXPOSE 9999
CMD ["./runS"]
