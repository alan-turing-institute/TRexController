FROM node:14

COPY src /app
WORKDIR /app
RUN npm install
EXPOSE 8080
CMD [ "node", "index.js" ]
