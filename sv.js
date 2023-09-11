const http = require("http");
const WebSocket = require("ws");
const socket = require("socket.io");

function stringify(dicionario){
  var dicionario=JSON.stringify(dicionario);
  dicionario=dicionario.replace(/"/g,'');
  dicionario=dicionario.slice(1,dicionario.length-2)
  console.log(dicionario)
  return dicionario;
}
function parse(dicionario){
  var separado=dicionario.split(",");
  var dici={};
  for (i=0;i<separado.length;i+=2){
    dici[separado[i]]=dici[separado[i+1]];
  }
  return dici;
}
// Crie um servidor HTTP básico
const server = http.createServer((req, res) => {
  // Lógica para lidar com solicitações HTTP (pode ser diferente da lógica WebSocket)
  // Por exemplo, responder a solicitações HTTP regulares
  res.writeHead(200, { "Content-Type": "text/plain" });
  res.end("Servidor HTTP ativo!");
});

// Crie um servidor WebSocket que utiliza o mesmo servidor HTTP
const wss = new WebSocket.Server({ server });

wss.on("connection", (ws) => {
  console.log("conectado");
  // Lógica para lidar com conexões WebSocket
  // Aqui, você pode receber mensagens do cliente WebSocket e enviar mensagens de volta
  ws.send(stringify({"tipo":"alo","aian":"eia"}));
  var d=new Date();
  var t=false;
  ws.on("message",(data)=>{
    console.log(parse(data.toString()));
    console.log(t);
  })
  ws.on("data",(data)=>{
    console.log(data.toString());
    ws.send("enviado")
  })
  ws.on("close",()=>{
    console.log("fechado")
    // ws.destroy();
  })
});

// Associar o servidor WebSocket a uma rota WebSocket específica ("/data" neste caso)
var upgrades=[]
var u=0;
server.on("upgrade", (request, socket, head) => {
    u++;
    if (u==0){
    if (request.url === "/data") {
        console.log("recebeu");
        wss.handleUpgrade(request, socket, head, (ws) => {
            // wss.emit("connection", ws, request);
        });
    } else {
    // Feche a conexão se a rota não for "/data"
        //socket.destroy();
    }
    }
});
// Inicie o servidor HTTP na porta 3000
server.listen(3000, () => {
  console.log("Servidor HTTP em execução na porta 3000.");
});
