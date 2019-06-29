import anime from './lib/anime.es.js';

var mat = [], mejorcamino = [], n=0, m=0

document.querySelector('#inicializar').onclick =async function inicializar(){
    m = document.getElementById("filas").value, n = document.getElementById("columnas").value /*Se editan estas lineas para indicar el numero de filas y columnas, ademas de las lineas mat[][] que se llenan manualmente*/

    for(var i = 0; i <= m; i++){
      mat[i] = new Array(n+1)
      mejorcamino[i] = new Array(n+1)
    }

      for(var i=0; i<m; i++){
        for(var j=0; j<n; j++){
          var cantidad = ""
          do{
            cantidad = prompt("Ingrese la cantidad ubicada en la casilla ("+i+","+j+"). Valores de 1 a 9.","0")
            mat[i][j] = parseInt(cantidad)
          }while(parseInt(cantidad)>9 || parseInt(cantidad)<1)
        }
      }

       var bacterias = document.createElement("img")
       bacterias.setAttribute("src", "bacterias.png")
       bacterias.setAttribute("style", "position: absolute; left: 10px; z-index: 999")
       bacterias.style.visibility = 'hidden'

       document.getElementById("animacion").appendChild(bacterias)

      for(var i=0; i<m; i++){
        for(var j=0; j<n; j++){

        //Aprovechamos este for para hacer mejorcamino[][] de 3 dimesiones
        mejorcamino[i][j]=new Array()

        var celda = document.createElement("div")
        celda.setAttribute("id", ""+i+"_"+j)
        celda.setAttribute("class", "celda")
        celda.style.width = ""+Math.floor(100/n)+"%"
        celda.style.paddingTop = ""+Math.floor(100/n)+"%"

        var dato = document.createElement("div")
        dato.setAttribute("class", "text")
        dato.style.visibility = 'hidden'
        dato.innerHTML = "0"

        celda.appendChild(dato)

        document.getElementById("animacion").appendChild(celda)
        }
        document.getElementById("animacion").appendChild(document.createElement("br"))
      }
      window.scrollTo(0,document.documentElement.scrollHeight);
      bacterias.style.height = anime.get(celda, 'height', 'px')

      for(var i=0; i<m; i++){
        for(var j=0; j<n; j++){
          let cantidad = mat[i][j]
          var celda = document.getElementById(""+i+"_"+j)
          var dato = celda.getElementsByClassName('text')[0]

          var img = document.createElement("img")
          img.setAttribute("src", "frasco.png")
          img.setAttribute("style", "position: absolute; top: 5px;")
          img.style.left = ''+anime.get(dato, 'width', 'px')
          img.style.height = ''+anime.get(dato, 'height', 'px')

          celda.appendChild(img)

          var anim = anime.timeline({
            targets: img,
            duration: 1000,
          })
          anim.add({
            translateX: parseInt(anime.get(celda, 'height'))/3,
            rotate: -120,
            scale: 2,
            complete: function (anim) {
              dato.style.visibility = 'visible'
            },
          }).add({
            targets: dato,
            innerHTML: [0, cantidad],
            round: 1,
          }).add({
            translateX: 0,
            rotate: 0,
            scale: 1
          })
          await anim.finished
        }
      }
     for(var i = 0; i <= m; i++){
        mat[i][n] = 90001
     }
     for(var i=0; i <=n; i++){
         mat[m][i] = 90001
     }

     let an
       for(let i = m-1; i >=0; i--){
         let an2 = anime.timeline({duration: 300,})
         an2.add({
           targets: document.getElementById("linea1"),
           backgroundColor: "#2196F3",
         }).add({
             targets: document.getElementById("linea1"),
             backgroundColor: "#757575"
         });
         await an2.finished
           for(let j = n-1; j >=0; j--){
             an2 = anime.timeline({duration: 300,})
             an2.add({
               targets: document.getElementById("linea2"),
               backgroundColor: "#2196F3",
             }).add({
               targets: document.getElementById("linea2"),
               backgroundColor: "#757575"
             }).add({
               targets: document.getElementById("linea3"),
               backgroundColor: "#2196F3",
             }).add({
               targets: document.getElementById("linea3"),
               backgroundColor: "#757575"
             });
             await an2.finished
             celda = document.getElementById(""+i+"_"+j)
             mejorcamino[i][j].push(celda)
             an = anime.timeline({
               targets: celda,
               duration: 2500,
               autoplay: true
             });
             an.add({
               backgroundColor: '#ff3333',
               scale: [
                 {value: .1, easing: 'easeOutSine', duration: 100},
                 {value: 1, easing: 'easeInOutQuad', duration: 500}
               ],
               begin: function(anim) {
                 document.getElementById('titulo').innerHTML = "Vamos a buscar el camino con menor cantidad de químicos desde ("+(i+1)+","+(j+1)+")"
                 window.scrollTo(0,document.documentElement.scrollHeight);
               },
             });
             if(i != m-1 || j!= n-1){
               let adyacentes, todas, menor, menorval= 0
               if(i != m-1){
                 if(j!= n-1){
                   let abajo = document.getElementById(""+(i+1)+"_"+j), derecha = document.getElementById(""+i+"_"+(j+1))
                   adyacentes = new Array(abajo,derecha)
                   todas = new Array(celda,abajo,derecha)
                   if(parseInt(abajo.getElementsByClassName("text")[0].innerHTML)<parseInt(derecha.getElementsByClassName("text")[0].innerHTML)){
                     menor = abajo
                     mejorcamino[i][j] = mejorcamino[i][j].concat( mejorcamino[i+1][j])
                     menorval=parseInt(menor.getElementsByClassName("text")[0].innerHTML)
                   }else{
                     menor = derecha
                     mejorcamino[i][j] = mejorcamino[i][j].concat( mejorcamino[i][j+1])
                     menorval=parseInt(menor.getElementsByClassName("text")[0].innerHTML)
                   }
                 }else{
                   adyacentes = new Array(document.getElementById(""+(i+1)+"_"+j))
                   menor = document.getElementById(""+(i+1)+"_"+j)
                   mejorcamino[i][j] = mejorcamino[i][j].concat( mejorcamino[i+1][j])
                   menorval=parseInt(menor.getElementsByClassName("text")[0].innerHTML)
                   todas = new Array(celda,document.getElementById(""+(i+1)+"_"+j))
                 }
               }else{
                 adyacentes = new Array(document.getElementById(""+i+"_"+(j+1)))
                 menor = document.getElementById(""+i+"_"+(j+1))
                 mejorcamino[i][j] = mejorcamino[i][j].concat( mejorcamino[i][j+1])
                 menorval=parseInt(menor.getElementsByClassName("text")[0].innerHTML)
                 todas = new Array(celda,document.getElementById(""+i+"_"+(j+1)))
               }
               anime({
                 targets: document.getElementById("linea4"),
                 backgroundColor: "#2196F3",
                 delay: 900,
                 duration: 9000,
               }).finished.then(function(){
                 anime({
                   targets: document.getElementById("linea4"),
                   backgroundColor: "#757575"
                 });})
               an.add({
                 targets: adyacentes,
                 backgroundColor: '#ffff66',
                 begin: function(anim) {
                   document.getElementById('titulo').innerHTML = "Se compara cuál de los adyacentes es menor"
                 },
               }).add({
                 targets: menor,
                 backgroundColor: '#73e600',
                 begin: function(anim) {
                     document.getElementById('titulo').innerHTML = "El menor es el: "+menorval
                 },
               }).add({
                 targets: celda.getElementsByClassName("text")[0],
                 innerHTML: [parseInt(celda.getElementsByClassName("text")[0].innerHTML), parseInt(celda.getElementsByClassName("text")[0].innerHTML)+menorval],
                 easing: 'linear',
                 round: 1,
                 begin: function(anim) {
                     document.getElementById('titulo').innerHTML = "Se suma el valor del menor"
                 },
                 change: function(anim) {
                   celda.getElementsByTagName('img')[0].style.left = ''+anime.get(celda.getElementsByClassName('text')[0], 'width', 'px')
                 },
               }).add({
                 targets: mejorcamino[i][j],
                 backgroundColor: "#3A63F6",
                 begin: function(anim) {
                   //mostramos texto
                   document.getElementById('titulo').innerHTML = "El camino con menor cantidad de químicos para llegar al destino desde la casilla (" + (i+1) + "," + (j+1) + ") es:"
                   window.scrollTo(0,document.documentElement.scrollHeight);
                 },
               }).add({
                 targets: todas.concat(mejorcamino[i][j]),
                 duration: 1,
                 backgroundColor: '#f5f5f5',
               });
             }else{
               an.add({
                 targets: celda,
                 backgroundColor: '#f5f5f5',
               });
             }

             await an.finished
             if(i != m-1 || j!= n-1){
               mat[i][j] += Math.min(mat[i+1][j], mat[i][j+1]);

             }
           }
       }
       anime({
         targets: mejorcamino[0][0],
         backgroundColor: "#3A63F6",
       })
       anime({
         targets: celda,
         backgroundColor: '#73e600',
         begin: function(anim) {
             document.getElementById('titulo').innerHTML = "La menor cantidad de químicos que se pueden encontrar los microbios para llegar a su destino es: "+celda.getElementsByClassName("text")[0].innerHTML
             window.scrollTo(0,document.documentElement.scrollHeight);
         },
       });
       anime({
         targets: document.getElementById("linea5"),
         backgroundColor: "#2196F3",
       });
       console.log( mat[0][0]);


      /*
      *   MOVIMIENTO DE BACTERIAS POR EL MEJOR CAMINO
      */

      bacterias.style.visibility = 'visible'

       let a=0,b=0,derecha, abajo,bac
       while(a<m && b<n){
         if(a==m-1 && b==n-1)
          break
         if(a<m-1)
          abajo = document.getElementById(""+(a+1)+"_"+b)
         if(b<n-1)
          derecha = document.getElementById(""+a+"_"+(b+1))
         if(parseInt(derecha.getElementsByClassName("text")[0].innerHTML)<=parseInt(abajo.getElementsByClassName("text")[0].innerHTML)){
           b++
           bac = anime({
             targets: bacterias,
             translateX: b*parseInt(anime.get(celda, 'height'))
           })
           await bac.finished
         }else{
           a++
           bac = anime({
             targets: bacterias,
             translateY: a*parseInt(anime.get(celda, 'height'))
           })
           await bac.finished
         }
       }

  }
