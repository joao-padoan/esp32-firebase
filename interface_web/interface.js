const firebaseConfig = {
  apiKey: "AIzaSyDTm3ZTfCnSEMPIH6zu8rwWWzsC_B02AMU",
  authDomain: "sensor-8a60d.firebaseapp.com",
  databaseURL: "https://sensor-8a60d-default-rtdb.firebaseio.com",
  projectId: "sensor-8a60d",
  storageBucket: "sensor-8a60d.appspot.com",
  messagingSenderId: "711748081531",
  appId: "1:711748081531:web:f83861d367c5fd36ae4fde",
  measurementId: "G-WVRD7T95YQ",
};

firebase.initializeApp(firebaseConfig);

var variavel1 = document.getElementById("variavel1");
var temperatura = firebase.database().ref().child("valor");
var frequencia = firebase.database().ref().child("freq");
var variavel2 = document.getElementById("variavel2");

/* Função de geração de númericos pseudo-aleatórios */
function getData() {
  return Math.random();
}
var mudar;
var changeV = () => {
  mudar = document.getElementById("myInput").value;
  frequencia.set(Number(mudar));
};

/* Recebe do firebase os dados do sensor de temperatura */
var temp;
function getTemperatura() {
  temperatura.on("value", function (datasnapshot) {
    var arru1 = datasnapshot.val();
    variavel1.innerText = datasnapshot.val();
    arru1 = Number(arru1);
    temp = arru1;
  });
  frequencia.on("value", function (datasnapshot) {
    variavel2.innerText = datasnapshot.val();
  });
  return temp;
}

Plotly.newPlot(
  "temperatura",
  [
    {
      y: [getTemperatura()],
      mode: "lines+markers",
      connectgaps: true,
    },
  ],
  { displayModeBar: true, width: 1800, height: 800 }
);

count = 0;
setInterval(function () {
  Plotly.extendTraces("temperatura", { y: [[getTemperatura()]] }, [0]);
  count++;
  if (count > 1000) {
    Plotly.relayout("temperatura", {
      xaxis: {
        range: [count - 1000, count],
      },
    });
  }
}, 15);
