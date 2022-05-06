# Monkey Delivery

## Documento de diseño de videojuego

### MoonKey Studios

gamesmoonkey@gmail.com

Versión 1.4 – 30 de abril de 2022

## Datos generales:

**Género**: Aventura

**Subgéneros**: Exploración, Gestión y Mundo abierto

**Público objetivo*:
- Edad: +10 años
- Sexo: Hombre/Mujer
- Idioma: Español

**Plataformas disponibles**: PC

**Requisitos mínimos y recomendamos**: Que tu ordenador mueva el buscaminas online

## Hitos y objetivos:

**Fecha de propuesta del concepto**  
a  
Lograr concebir una idea atractiva tanto para el equipo como el consumidor que pueda ser llevada a cabo.

**Fechas de pre-producción**  
a  
Haber desarrollado la idea, teniendo todos los puntos importantes de la experiencia definidos para poder realizar la producción sin tener a penas que tocar el diseño y con una hoja de ruta que permita a cualquier mieembro del equipo saber que tiene que realizar en su tarea sin dpeender de tiempos de reuniones extra.

**Fechas de producción**  
a  
Tener un juego completamente jugable, con la mayor parte del contenido disponible. Con toda la arquitectura completada para poder añadir y realizar las modificaciones necesarias rápidamente y sin dificultades.

**Fecha de lanzamiento**  
06/05/2022  
Tener un juego completamente jugable, con todo el contenido disponible y estructurado en una historia. Sin bugs que afecten a la experiencia de forma relevante.


# 1. Datos generales

## Alcance del proyecto:

### Escenarios disponibles: 

Un solo nivel de 10.000x10.000 píxeles divido en diferentes biomas.

### Objetos:

**No consumibles**: 
-Linterna cónica
-Linterna circular
-Botas viejas
-Botas
-Pico 
-Patines
-Monopatin

**Consumibles**:
-Bebida Energética
-Repelente Anti Bananas
-Banana
-Cafe

**De la historia**:
-Diferentes paquetes a entregar, uno para cada misión

**Personajes**:
-Erizo PatasLargas
-Cocodrilo Croki
-Hipopótamo Pepi
-Cebra Ceci
-Wallaby Willy
-Capitán Pescaniva
-Tucana Aitana
-Rana
-Tortuga

**Especiales**:
-Mapa
-Bancos
-Tienda

### Descripción

En Monkey Delivery tomarás el papel de Monkey, un pequeño mono que se dedica a repartir paquetes a los vecinos de Selva Banana, su localidad natal. Simultáneamente, deberás mantener tu sueño a raya, durmiendo cuando sea necesario. En tu misión habrá enemigos que asustarán a Monkey, por lo que tendrás que evitarlos. Al completar trabajos recibirás dinero, que te será útil para comprar diferentes materiales y objetos en las tiendas.

### Aspectos generales

Es un juego que se basará fundamentalmente en la exploración: conociendo las ubicaciones tanto de los vecinos como de los enemgios, obteniendo recompensas escondidas por el mapa y descubriendo el rico mundo donde se encuentra la aldea de nuestro protagonista.  
El segundo elemento que más relevancia cobra será el de la gestión. La principal recompensa de las misiones, además de conocer la historia del pueblo donde has llegado, es la de monedas con la que adquirir objetos en la tienda que te ayudarán en las futuras misiones. Permitiendote llegar más lejos y desenvolverte mucho más hábilmente por el mundo; ya sea mediante consumibles o mejoras mediante el equipamiento de objetos como botas.
Con esto buscamos que el jugador pase una experiencia agradable descubriendo un mundo colorido mientras juega y experimenta con las diferentes mecánicas y situaciones que se le brindarán en este mundo abierto.

### Jugabilidad
 
 Estarás moviendote continuamente por el mapa, desplazarte será tu fundamental herramienta para llegar a todos los paquetes. La otras mas relevantes son el uso d elas linternas para eliminar a los enemigos con ellas y despejarte el camino así como el uso de objetos ya sea el mapa para ver el mejor camino a tu objetivo o equiparte las botas para llegar máa rápido a tu destino.


## 2.1 Mecánica

### 2.1.1. Mecánicas del personaje

**Moverse**: Se podrá desplazar en 8 direcciones, desplazandose de forma libre en el eje x e y. Se podrá esprintar para aumentar la velocidad del movimiento a costa de gastar más energía.

**Energía**: Esta es limitada y se irá gastando con el movimiento, en caso de que llegue a 0, su velocidad se verá muy reducida haciendole mucho más complicado el reparto. Se verá reflejada en la esquina izquierda en forma de barra y se podrá recuperar tanto durmiendo como con consumibles, o un porcentaje pequeño si te quedas quieto. A su vez se podrá regenerar un 45% si se queda quieto.

**Miedo:** El sentimiento que siente Monkey cuando ve a los enemigos. Por norma general estos rellenan la barra al estar cerca del jugador y si llega al máximo, el jugador se desmayará y reaparecerá en el centro del pueblo. Se puede reducir con consumibles o durmiendo.

**Inventario**: El jugador tiene 6 slots de inventario para guardar los objetos que compre y  otro más para el paquete u objeto de la misión, este último slot no es inderactuable. Los demás slots podrán ser seleccionados por el jugador y usados, ya sea tomando el consumible o equipandose y desequipandose el objeto marcado.

### 2.1.2. Mecánicas de los objetos

**Interactuar**: Mecánica general de todos los objetos, en el caso de aquellos no consumibles los equipo o desequipa. En el caso de los consumible estos son gastados y las estadísticas del jugador modificadas. Hay casos especiales.

**Botas viejas/botas**: Objetos equipables que te permiten desplazarte a mayor velocidad sin suponer un gasto extra de energía. EL porcentaje de velocidad extra de las segundas es mayor que el de las primeras.

**Linterna cónica y circular**: Objetos equipables que crearán un halo de luz frente al jugador y alrededor de él respectivamente. Este halo acabará con los enemigos que se queden un tiempo determinado bajo él, habriendo el camino al jugador.

**MonkeyCola**: Consumible que reduce el miedo un 20% al jugador si esta se encuentra por debajo del 80% del máximo u otro porcentaje si supera este.

**Banana**: Consumible que recupera energía al jugador, siendo un porcentaje del 10% y un 25% si estas en minimos.

**Repelente**: Consumible que reduce el factor de miedo proveniente de los enemigos durante un tiempo.

**Mapa**: Objeto especial que se puede desplegar, muestra una vista general del mapa y se puede poner un puntero para ubicar el objetivo de la ruta con mayor facilidad.

**Pico**: Elemento que se te da tras completa la primera tanda de misiones y que sirve para romper rocas y acceder a nuevas zonas del mapa.

### 2.1.3. Mecánicas de escenario

**Minimapa**: Muestra en la esquina inferior izquierda una visión general de la zona donde se encuentra el mono en tiempo real para ubicarse adecuadamente.

**Bancos**: Dormir en ellos te permitirá recuperar la energía y el miedo. Estan ubicados en zonas seguras para que puedas descansar tranquilo.

**Panel de misiones**: Selector de misiones que las muestra de forma gráfica con una breve descripción y detalles. Es el lugar donde se cogen los nuevos encargos.

**Tienda**: Lugar interactuable en la zona central del pueblo donde podrás adquirir productos.

**Objetos de misión**: Objetos sueltos por el mapa que al recogerlos permiten realizar misiones de encargo.

**Casas de vecinos**: Diferentes ubicaciones donde se encuentran los vecinos al seleccionar sus misiones.

**Rocas**: Elementos por el mapa que bloquean caminos y deberán ser rotos con el pico para poder pasarlos.

**Cofres**: Repartidos por el mapa, los abrirás para conseguir recompensas. Fomentarán la exploración.

### 2.1.4 Mecánicas de enemigos

**Patrullar -- Común**: los enemigos con esta mecánica se moverán dentro de una zona, escogiendo un punto aleatorio dentro de esta. Este movimiento comienza cuando spawnean. No se detienen nunca, salvo en el caso de que además tengan la mecánica de perseguir al jugador.

***Efecto del enemigo***: Cada enemigo provocará un efecto distinto en el jugador. Ver apartado 4.3 parte de los enemigos.

**Ver y perseguir al jugador -- Toro**: Los enemigos que persiguen al jugador tendrán un campo de visión. Si el jugador entra, comienzan una persecución que dura 3 segundos. Si cuando pasen los 3 segundos, el jugador sigue en el campo de visión (el actual) la persecución continúa. Esto ocurre hasta que el jugador salga del campo de visión o el enemigo se aleje x distancia de la posición en la que estaba cuando empezó la persecución. Cuando esta acabe, vuelve a ese punto y sigue el recorrido.

**Somnolencia -- Planta**: Cuando el jugador entra en el rango del enemigo su nivel de sueño aumentará x.

**Robo -- Múrcielago**: Cuando el jugador entre en el rango del enemigo  y mientras esté en contacto con este, le quitará una moneda por segundo.

**Ralentización -- Escorpión**: Cuando el jugador entre en el rango del enemigo y mientras esté en contacto con él, el jugador reducirá su velocidad  ⅓.


## 2.2 Dinámicas

### 2.2.1 Entrega de paquetes

Las misiones del juego. Serán el centro de la experiencia. LLegar a los vecinos en sus ubicaciones dispersas por el mapa para entregar un paquete será el principal desafío que se encontrará Moneky en esta aventura. Siendo de 3 tipos : Normales, express y Paquetes perdidos. Darán tanto recompensas monetarias como información sobre el pueblo, lo que conformará el eje de la trama. 

### 2.2.2 Enfrentamientos con enemigos

Los enemigos se encontrarán por todo el mapa y cuánto más te alejes del pueblo mayor será el desafío que supondrán. Acabar a ellos con las linternas, esquivarlos, controlar la estamina que te harán gastar y el miedo que te harán pasar será clave para poder viajar por el mundo que se nos presenta.

### 2.2.3 Exploración

Se nos da un mundo abierto amplioo y lleno de secretos. Conocerlo, los caminos más rápidos como donde hay más enemigos, te permitirán moverte. A su vez, encontrar los cofres que oculta en mundo o las casas de los vecinos te darán beneficios tanto económicos como estrátegicos a la hora de arontar los nuevos encargos.

### 2.2.4 Gestión de recursos

La economía será un pilar fundamental en el peligroso mundo por el que te moverás. Saber en que objetos permanentes invertir para aumentar tus posiiblidades a la vez que adquirir consumibles para salir de situación peliagudas será la diferencia entre triunfar y fracasar en esta aventura.

### 2.2.5 Enemigos

**Toro**: Persigue al jugador cuando entra en su rango. Es rápido y peligroso.

**Gato**: Asusta al jugador cuándo apsa cerca suya, resiste más.

**Escorpión**: Frena al jugador al pasar junto a él.

**Murciélago**: Al pasar junto al él te roba monedas.

## 2.3 Mapa

**Dimensiones**: El mapa será construido en Tiled, contará con unas dimensiones lo suficientemente amplias para colocar los personajes de todas las misiones de manera realista y que el viaje de un punto a otro pueda suponer realmente un desafío.

**Zonas**: El mapa se dividirá en 7 zonas principales, cada una con elementos diferentes y característicos tanto a nivel jugable como visual:

-*Zona del pueblo*: zona inicial, con la menor densidad de enemigos. Tanto la base como la tienda y el panel de misiones se encuentran aquí.

-*Praderas y huerto del norte*: zona abierta en la parte noreste del mapa donde se encontrará una cantidad de enemigos reducida y bastante espacio para moverte.

-*Río*: zona que cruza el centro del mapa de este a oeste, para cruzar de un lado al otro se usarán los puentes y habrá varias islas con casa. Con una cantidad de enemgios moderada.

-*Casas gemelas y alrededores*: zona al sureste del mapa con dos casas solitarias y pequeñas praderas. Las casas supondrán una zona segura de los enemigos que habitan la zona.

-*Cementerio*: zona peligrosa en la zona sur del mapa, mucho más tenebrosa que el resto de lugares que conforman el pueblo.

-*Praderas del sureste*: zona abierta con alta presencia de enemigos y una pequeña casa en las zonas más bajas.

-*Playa del sur*: zona más al sur del mapa que deja de lado la vegetación y presenta una playa de arena con acantilados ante ella, peligrosa y con enemigos. Una isla y una choza se encuentran en este área tan distante.

## 2.4 Misiones


Descripción del encargo

Objeto a entregar

Punto de entrega

Recompensa

Tiempo

Toda esta información se verá por pantalla, en una nota.

En el punto de entrega, que será una de las casas, aparecerá el vecino en la puerta, para que se pueda hablar con él. Aparecerá solo en los momentos en que pueda recibir un paquete, es decir, si la misión activa es para él.

Para completar una misión, el jugador deberá desplazarse hasta el punto de entrega, y entregar el objeto. Al hacerlo, el vecino le contará al jugador una historia relacionada con el paquete que le acaba de entregar (en tono humorístico) y recibirá la recompensa monetaria correspondiente. Además, aparecerá en su casa un nuevo objeto decorativo, en alguna forma relacionado con la misión o el vecino. Esto ocurre de forma automática. El vecino se irá de la puerta (desaparecerá) cuando nos alejemos una cierta distancia de él (cuando no se vea en pantalla).

Cuando la misión se activa, comienza un temporizador desde un tiempo máximo hasta 0. Esto indica el dinero que recibirá al completar la misión: cuanto más tiempo pase, menos dinero recibirá (dentro de unos límites mínimos y máximos). Cuando llegue a 0, el temporizador se para y recibirá el dinero mínimo (si se trata de una entrega estándar, ver más abajo). Cada misión tiene un tiempo inicial dentro del que recibe el máximo dinero aunque el temporizador haya avanzado.

`	`Al mismo tiempo, las misiones se dividen en varios tipos:

`	`1- Entrega estándar: El jugador recibe en su inventario el objeto a entregar (un paquete).Como tal no tiene límite de tiempo. Pero si tarda demasiado recibirá menos dinero. Si se completa en un tiempo determinado recibirá el máximo de dinero. Esta misión no desaparece aunque el temporizador llegue a 0. Si llega a 0 recibe el la cantidad mínima de dinero.

`	`2- Entrega express: Igual a la estándar, pero cuando el temporizador llegue a 0, además de pararse, borra el paquete del inventario y la misión activa de la pantalla. Se ve por pantalla el tiempo restante.

`	`3- Entrega personalizada: En este caso no recibes el objeto a entregar, sólo se te da la descripción del encargo en la oficina de correos. Esta descripción te dará la información necesaria para encontrar un objeto en algún lugar del mapa, que se habrá spawneado en un punto predeterminado en el momento de aceptar la misión. Este objeto será interactuable, y se añadirá al slot del inventario específico para los paquetes. Una vez se recolecte, se podrá hablar con el vecino indicado y completar la misión para recibir la recompensa. Antes de recoger el objeto, el vecino no es visible.

Temporizador de pedidos: Cuando se activa una misión, se inicia un temporizador con un tiempo definido por la misión. Con el paso del tiempo de juego, ese temporizador disminuye hasta llegar a 0. Cada misión manejará lo que ocurre según el tiempo restante en su temporizador (mencionado arriba en la descripción de las misiones).

Spawn de enemigos: Se determinan zonas en las que pueden aparecer enemigos y una lista de enemigos que pueden aparecer en esas zonas. Un generador spawnea uno de estos hasta que se alcance el nº máximo de enemigos en esa zona (que también se debe determinar). Si en esa zona un enemigo es eliminado, al pasar x horas de juego debe aparecer otro en esa zona.

Diálogos con los vecinos:  Cuando el protagonista entrega el pedido salta un diálogo con el vecino, en relación con el paquete. Si el paquete no es el correcto, no ocurre nada. Únicamente se abre el diálogo al completar la misión correctamente.



# 3 Datos técnicos y estéticos

## 3.1 Controles

- A,W,S,D : Para moverse hacia los lados
- Shift: Para correr
- E: Para interactuar con objetos
- M: Abrir el mapa
- 1, 2, 3, 4, 5, 6: utilizar objeto del inventario


## 3.2 Cámara

Monkey Delivery es un juego con vista top down, el jugador se presenta siempre en el centro de la pantalla. Con un rango amplio podemos ver un gran área al rededor dl jugador con lo que podemos evitar enemigos y encontrar ubicaciones más fácilmente.

## 3.3 Gráficos

El estilo utilizado en Monkey Delivery será Pixel Art. Se tratará de un entorno colorido, para darle un ambiente frenético.

Con un número de píxeles reducido tanto en personajes como escenario consiguiendo un apartado gráfico llamativo y simple que agrade y no canse al jugador.

La paleta utilizada será de colores claros y llamativos para dar una ambientación alegre y desenfadada. Dando contrastes con la historia planteada y el cementerio, que debido a su naturaleza girará en torno a colores más oscuros.

## 3.4 Música y Sonido

-Habrá música constante en el juego. Diferente en los menús e ingame.

-Todos los enemigos tendrán un sonido específico y reconocible para el jugador.

-Las diferentes acciones como completar una misión, caminar... Contarán con efectos de sonido.

## 3.3 Interfaz

### 3.3.1 Hud InGame

-Tendremos en la zona superior izquierda un panel que mostrará la información general del jugador: energía, miedo, monedas actuales y cofres restantes. En el lado opuesto tendremos un panel texto cuando estemos en una misión que nos informará de la dirección a seguir.

-En la parte inferior, ocupando los 2/3 centrales de la pantalla tendremos el inventario repartido en 7 slots. A la derecha de este encontramos un minimapa que se puede desplegar pàra ocupar toda la pantalla y mostrar de forma más detallada el mundo del juego.

-En la zona superior derecha tendremos el botón de pausa.

#### 3.3.1.1 Tienda

Se mostrará al interactuar con la tienda y donde mostrará en la zona inferior izquierda los controles de esta. En la zona central inferior las monedas actuales y el coste de cada objeto y en la zona central ocupando casi toda la pantalla los objetos disponibles para comprar organizados horizontalmente. 
Dentendrá la acción y se creará sobre un marco que ocupa toda la pantalla.

#### 3.3.1.2 Panel de Misiones

Se mostrará al interactuar con el panel de misiones y mostrará las misiones disponibles en paneles organziados horizontalmente, en la parte inferior izquierda estarán los controles.
Al seleccionar una misión esta desaparecerá y dejará su hueco vacío.
Se dibujará sobre un panel que ocupará toda la pantalla y detendrá el tiempo.

#### 3.3.1.3 Text Box

Se mostrará cuando se dispare un evento de diálogo. Ocupará la parte central de la zona inferior e irá mostrando el texto progresivamente sobre un panel. Se podrá acelerar y una vez concluido cerrar. El jugador quedará inmovilizado mientras este este desplegado.

### 3.3.2 Menús

**Menú principal**:

Menú que se muestra al abrir el juego y desde donde podremos acceder a una partida, las opciones o volver a salir. Contará con estos 3 botones en la zona central, de arriba a abajo. El título del jeugo se encontrará sobre ellos y un fondo que ocupe tod la pantalla.

**Menú de opciones**:

Menú que se accede desde el de pasua o el principal. En el encontramos un botón de volver atrás. en la zona central encontramos 4 sliders que se pueden ajustar a decisión del jugadoor.
Estarán ubicados dos a dos y sus funciones serán, empezando por el de la zona superior izquierda: 
-Volumen general
-Música
-Brillo
-Efectos

**Menú de pausa**:

Menú que see podrá desplegar desde el juego y dentendrá toda la acción. Con una distribución similar al menú principal y con un fondo que ocupa toda la pantalla dará las siguientes opciones:
-Reanudar
-Ajustes, que abre el menú de ajustes
-Volver, para regresar al menú principal

**Créditos**:

Menú que se puede acceder desde el menu principal donde irán mostrándose los créditos de forma continua de todos los integrantes y con un botón de volver atrás en la zona inferior izquierda.


# 4 Historia

Contenido

Mencionar el tipo de elementos que se van a necesitar (imágenes, sonidos, música…)

Historia

Párrafos e ilustraciones donde se describe todo el trasfondo narrativo del juego, los antecedentes que no llegamos a jugar y también la parte de la historia que sí se cubre con la jugabilidad. Se puede enumerar los personajes desde un punto de vista dramático, aunque si hay información jugable asociada a ellos, es mejor tenerlos en una lista aparte (sección 8).

Si hay cinemáticas o grandes fragmentos de texto, puede incluirse una lista completa en una sección aparte, o tener alguna base de datos u hoja de cálculo que luego será utilizado por los traductores y revisores de textos.

Nota en el libro explica tu origen.

Cuando acabas todos los pedidos y vuelves a la oficina, te dicen que una puerta se ha abierto. Puedes cruzarla, y al hacerlo te encuentras a Jeff Bezos sentado en un váter dorado y te da un discurso de que es el mejor. Pulsas un botón y sale volando. Te sientas en su trono. Ahora eres tú el rey.

El repartidor de tu pueblo ha enfermado, por lo que el dueño te pide ayuda para repartir los paquetes a los vecinos. Esto se te explicará con un tutorial al inicio (despiertas en tu casa y te desplazas hasta la oficina). Cuando acabes las rondas predeterminadas, volverás a la oficina y acabará la historia principal.

Niveles

Párrafos e ilustraciones donde se describe en detalle todos los niveles o misiones del juego, numerados como 6.1, 6.2, 6.3, etc. Si se reutiliza una misma localización para varios niveles o misiones distintos, se podría tener una lista aparte únicamente de localizaciones.

El juego consta de un mapa en el cual, se encuentran repartidas todas las misiones:

- Misión Erizo (Dificultad Difícil): El jugador ha de llevarle una pata de un sillón y un sombrero de copa , estos se encontraran en distintas localizaciones del mapa y se dispondrá 3 minutos para poder coger los objetos y llevarselos.
- Historia: Al erizo PatasLargas se le ha roto el sillón debido a que está muy gordo , de modo que se ha comprado una pata de sillón para poder arreglarlo y poder calentar su tremendo trasero en el sillon. Además a tan tremenda tragedia se le suma que no encuentra el sombrero de copa que tanto le gusta de modo que ha decidido que su primo el erizo PatasCortas le preste el suyo.
- Diálogo Final De La Misión(Lo dice el erizo): Muchas gracias por traerme la pata del sillón ahora podré sentarme y relajarme en mi querido sillón, de hecho voy a hablar con Ikea para conseguir un sillón a ti tambien y te puedas relajar.
- Misión de Ceci: El jugador tendrá 3 minutos para buscar por el camino de casa de Ceci a la oficina el rotulador y devolverselo. Como recompensa recibirás un bote con rotuladores.
- Descripción: La cebra Ceci ha perdido un rotulador negro de camino de su casa a la oficina de correos que es muy importante para ella debido a su terrible secreto que no quiere desvelar. Ayúdala a encontrarlo, quizás te desvele su secreto…

`	`-Diálogo final:  Hola, muchas gracias por devolverme mi rotulador. Ah, que por que lo necesito, bueno supongo que te puedo decir mi secreto, pero no se lo cuentes a nadie, ¿me oyes? Resulta que en verdad soy un caballo blanco pero siempre quise ser una cebra, así que me pinto las rayas. Pero tu shhhh. Toma esto por ayudarme a mantener mi secreto a salvo.

- Misión de Willy: El jugador tendrá 4 minutos para llegar al bosque, buscar los guantes (que estarán relativamente escondidos) y llevarselos de vuelta a Willy. Recibe un trofeo de ...el último puesto?!
- Descripción: El ualabí Willy es el boxeador más famoso de selva-sabana. Normalmente va a entrenar al bosque a darle unos puños al saco de boxeo que colgó del árbol más grande. Ha participado en numerosos combates (todos contra el árbol y en todos perdió…). Pero hoy no ha podido ir a entrenar porque no encuentra sus guantes, se los debió dejar en el bosque. ¿Podrías encontrarlos y devolvérselos?

`	`-Diálogo: Muchas gracias por encontrar mis guantes, sin ellos no podría ir a entrenar para ganar más combates (...). Toma esto en agradecimiento.

- Mision del Capitan Pescaniva: El jugador tendrá 5 minutos para buscar el chubasquero alrededor del lago y llevárselo. Recibes un barco en una botella de decoración.
- Descripción: El capitán Pescaniva suele ir a navegar a lo que él llama el gran mar, (que en verdad es un lago al lado de su casa). A pesar de ser un pez le da un miedo terrible el agua y mojarse por ello necesita llevar puesto su chubasquero, pero no lo encuentra. Seguramente lo perdió cerca del lago (porque tampoco se mueve mucho). Encuentralo y devuelveselo.

`	`-Diálogo:  Buenos días, oh, muchas gracias por encontrar mi chubasquero, toma esto como recompensa.

Personajes y enemigos

Párrafos e ilustraciones donde se describe en detalle todos los personajes del juego, tanto avatares del jugador, como enemigos u otros personajes no-jugables, hasta secundarios. Con todas sus características convenientemente recogidas en tablas uniformes..

Puede ayudar incluir retratos y arte conceptual de los personajes

Vecinos:

Erizo PatasLargas

Cocodrilo Croki

Hipopótama Pepi

Cebra Ceci

Wallaby Willy

Capitán Pescaniva

Tucana Aitana

Ranae

Tortuga

Pavo Real

Enemigos:

Planta Piraña (nombre provisional): Si el jugador se encuentra en su rango esta lanzará unas esporas que provocarán somnolencia (ver apartado 2.1.3 Mecanicas de enemigos).

Escorpión: Cuando el jugador entre en su rango ralentizará al jugador (ver apartado 2.1.3 Mecanicas de enemigos). Provoca 5% del total  miedo. Tiene la mecánica de patrullar.

Fantasmas:

Fantasma que persigue (toro): Provoca 15% del total miedo y tiene la mecánica de patrullar y perseguir

Fantasma estático (batpatt): Provoca un 10% del total de miedo y tiene la mecánica de patrullar


# 5 Referencias

- Pokemon (juegos antiguos)
- Animal Crossing
- Stardew Valley


##UML
![UML_Monkey_Delivery drawio](https://user-images.githubusercontent.com/82326243/152699560-aa794a2b-cd24-4e00-90fa-4dad823b08a2.png)
