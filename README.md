# Monkey Delivery

## Documento de diseño de videojuego

### MoonKey Studios

gamesmoonkey@gmail.com
(Grupo 02 de Proyectos 2)

WEB: https://miggon23.github.io/MonkeyDelivery/

## Datos generales:

![MenuMonkeyDelivery](https://user-images.githubusercontent.com/81906237/167201212-f09e7f67-3524-47cc-b67d-751f2bfffd32.png)

![JuegoBase](https://user-images.githubusercontent.com/81906237/167201218-8938fa44-572f-455e-b853-53592e363186.png)

**Género**: Aventura

**Subgéneros**: Exploración, Gestión, Aventura gráfica, Simulador y Mundo abierto

**Público objetivo*:
- Edad: +13 años
- Idioma: Español

**Plataformas disponibles**: PC

**Requisitos mínimos y recomendamos**: Que tu ordenador mueva el buscaminas online

**Nota:** Durante el desarrollo del juego, la bici y patines pasaron a ser botas (de diferentes calidades), y el pico pasó a ser una pala. Estos cambios son meramente visuales, ya que la funcionalidad la hemos mantenido. Cualquier referencia en este documento a estos elementos se puede sustituir por el sustituto.

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
- Diferentes paquetes a entregar, uno para cada misión.
- Algunos de estos se buscarán en el mapa.

**Personajes**:
- Tucana Aitana
- Hipopótamo Hipo
- Pavo Raúl
- Ajolote Julián
- Águila Francisco
- Conejo Carlos
- Rana Kermit
- Cocodrilo Cleon
- Zorro Zacarías

**Especiales**:
- Mapa
- Bancos
- Tienda
- Panel de misiones
- Rocas
- Cofres

### Descripción

En Monkey Delivery tomarás el papel de Monkey, un pequeño mono que se dedica a repartir paquetes a los vecinos de Todesfall, pueblo al que se ha mudado para trabajar. Simultáneamente, deberás mantener tu sueño a raya, durmiendo cuando sea necesario. En tu misión habrá enemigos que asustarán a Monkey, por lo que tendrás que evitarlos. Al completar trabajos recibirás dinero, que te será útil para comprar diferentes materiales y objetos en las tiendas. Mientras cumples tu trabajo, irás descubriendo el misterio que ocurrió en Todesfall, con lo que tus vecinos te contarán.

### Aspectos generales

 Es un juego que se basará fundamentalmente en la exploración: conociendo las ubicaciones tanto de los vecinos como de los enemgios, obteniendo recompensas escondidas por el mapa y descubriendo el rico mundo donde se encuentra la aldea de nuestro protagonista.  
El segundo elemento que más relevancia cobra será el de la gestión. La principal recompensa de las misiones, además de conocer la historia del pueblo donde has llegado, es la de monedas con la que adquirir objetos en la tienda que te ayudarán en las futuras misiones. Permitiendote llegar más lejos y desenvolverte mucho más hábilmente por el mundo; ya sea mediante consumibles o mejoras mediante el equipamiento de objetos como botas.
Con esto buscamos que el jugador pase una experiencia agradable descubriendo un mundo colorido mientras juega y experimenta con las diferentes mecánicas y situaciones que se le brindarán en este mundo abierto.

### Jugabilidad
 
 Estarás moviendote continuamente por el mapa, desplazarte será tu fundamental herramienta para llegar a todos los paquetes. La otras mas relevantes son el uso de las linternas para eliminar a los enemigos con ellas y despejarte el camino así como el uso de objetos, ya sea el mapa para ver el mejor camino a tu objetivo, equiparte las botas para llegar más rápido a tu destino, o usar consumibles para obtener mejoras puntuales.


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

![PanelMisiones](https://user-images.githubusercontent.com/81906237/167200881-98c7eace-c91c-4ecb-950c-22baf8333cb2.png)

Cada misión cuenta con:

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

Imagen de tutorial que se mostrará al jugador:
![Tutorial](https://user-images.githubusercontent.com/81906237/167200313-03971fee-54fa-4445-ad1a-b7e923991056.png)



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

![SantiagoTienda](https://user-images.githubusercontent.com/81906237/167200218-945683ae-d4f9-4de0-8d89-2d244f871b4d.png)


#### 3.3.1.2 Panel de Misiones

Se mostrará al interactuar con el panel de misiones y mostrará las misiones disponibles en paneles organziados horizontalmente, en la parte inferior izquierda estarán los controles.
Al seleccionar una misión esta desaparecerá y dejará su hueco vacío.
Se dibujará sobre un panel que ocupará toda la pantalla y detendrá el tiempo.

![PanelMisiones](https://user-images.githubusercontent.com/81906237/167200192-64cfb819-243d-4fe3-8e46-9b59541af813.png)


#### 3.3.1.3 Text Box

Se mostrará cuando se dispare un evento de diálogo. Ocupará la parte central de la zona inferior e irá mostrando el texto progresivamente sobre un panel. Se podrá acelerar y una vez concluido cerrar. El jugador quedará inmovilizado mientras este este desplegado.

### 3.3.2 Menús

**Menú principal**:

Menú que se muestra al abrir el juego y desde donde podremos acceder a una partida, las opciones o volver a salir. Contará con estos 3 botones en la zona central, de arriba a abajo. El título del juego se encontrará sobre ellos y un fondo que ocupe toda la pantalla.

![MenuMonkeyDelivery](https://user-images.githubusercontent.com/81906237/167200126-fe3e3489-af2d-43d4-b409-a4ec975468b0.png)

**Menú de opciones**:

Menú que se accede desde el de pasua o el principal. En el encontramos un botón de volver atrás. en la zona central encontramos 4 sliders que se pueden ajustar a decisión del jugadoor.
Estarán ubicados dos a dos y sus funciones serán, empezando por el de la zona superior izquierda: 
-Volumen general
-Música
-Brillo
-Efectos de sonido

![Ajustes](https://user-images.githubusercontent.com/81906237/167199969-3a4b299e-0e98-4914-baf8-fc5cc658d96a.png)


**Menú de pausa**:

Menú que see podrá desplegar desde el juego y dentendrá toda la acción. Con una distribución similar al menú principal y con un fondo que ocupa toda la pantalla dará las siguientes opciones:

-Reanudar
-Ajustes, que abre el menú de ajustes
-Volver, para regresar al menú principal

**Créditos**:

Menú que se puede acceder desde el menu principal donde irán mostrándose los créditos de forma continua de todos los integrantes y con un botón de volver atrás en la zona inferior izquierda.


# 4 Historia

**Contenido**:
EL juego cuenta con 3 niveles de 3 misiones cada uno. Cada misión está dirigida a un vecino (que cuenta con su spritesheet individual), y tiene una descripción distinta. Hay una misión de cada tipo por nivel. 
Al finalizar cada nivel, la tienda sube de nivel, es decir, muestra nuevos objetos. EL jugador obtiene un pico mejorado.

Los diálogos, tipos, y otros datos específicos de las misiones, pueden consultarte en resources.json (Dentro de /Images/config/), dentro del apartado "Missions" y "Dialogues".

**Historia**

Monkey se traslada al pueblo de Todesfall para trabajar como repartidor. Cuando llega todo parece normal, un pueblo muy agradable. Lo que no sabe, es que el anterior repartidor desapareció bajo misteriosas circunstancias mientras trabajaba en el pueblo. Comenzará a hacer misiones y cuando hable con los vecinos, al entregarles sus pedidos, éstos se irán de la lengua poco a poco, contando detalles curiosos sobre la historia, que el jugador podrá ir hilando para descubrir qué le paso al repartidor. La realidad es que los vecinos de Todesfall lo asesinaron a sangre fría porque estaban descontentos con el trabajo que hacía. Todos los vecinos, salvo el Águila y el Cocodrilo estuvieron implicados. El cocodrilo tiene miedo de sufrir el mismo destino, y está planeando su huída.
Cuando Monkey acabe todas sus misiones disponibles, aparece una nota en el tablón de misiones, dejada por Cleon el cocodrilo. Le dice que vaya al puerto, donde le está esperando con una barca lista para huir de allí.
En este momento saldrá una cinemática en la que se ve a ambos huyendo en el barco.

**Personajes y enemigos:**

Vecinos:
- Tucana Aitana
![NPC_Tucan](https://user-images.githubusercontent.com/81906237/167198516-2781e3fd-cab7-41c3-b293-2effbb04731d.png)

- Hipopótamo Hipo
![NPC_Hipo](https://user-images.githubusercontent.com/81906237/167198624-d81c197c-8dac-44fb-80e5-2b194c659e9b.png)

- Pavo Raúl
![NPC_Pavo](https://user-images.githubusercontent.com/81906237/167198635-dc797efa-768f-4320-8aa9-9e6ca894b8b9.png)

- Ajolote Julián
![NPC_Fish](https://user-images.githubusercontent.com/81906237/167198659-e6b118cd-c00a-4d0d-bfde-b5337050c3fa.png)

- Águila Francisco
![NPC_Eagle](https://user-images.githubusercontent.com/81906237/167198675-8732b919-9544-4512-81a8-4a26519066d5.png)

- Conejo Carlos
![NPC_Rabbit](https://user-images.githubusercontent.com/81906237/167198684-599ffa6e-3783-4b44-9dbb-5456eb52f328.png)

- Rana Kermit
![NPC_Frog](https://user-images.githubusercontent.com/81906237/167198697-79859310-d712-4f59-a9f3-599b81fa66fa.png)

- Cocodrilo Cleon
![NPC_Coco](https://user-images.githubusercontent.com/81906237/167198717-52ae0690-91b3-44b0-826a-a99f9283a859.png)

- Zorro Zacarías
![NPC_Fox](https://user-images.githubusercontent.com/81906237/167198721-75f2c045-1999-485a-8bd2-e1a6b80f3436.png)

Enemigos:
- Toro:
![bullSS_Default](https://user-images.githubusercontent.com/81906237/167198872-27b94cdf-d29d-4105-96cd-82aa687ca2ef.png)

- Murciélago:
![batSS_Default](https://user-images.githubusercontent.com/81906237/167198866-1babe4e0-322f-41c8-888e-9ae7eb654a99.png)

- Planta:
![plantSS_Orange](https://user-images.githubusercontent.com/81906237/167198943-0c8522d3-0da7-4cb7-a6ca-9c43e00a219a.png)
![plantSS_Purple](https://user-images.githubusercontent.com/81906237/167198947-003a3ac9-7b8d-47d7-8055-351699a201a6.png)
![plantSS_Red](https://user-images.githubusercontent.com/81906237/167198950-feab4102-b3ce-46ca-a316-a6f29b62ab9c.png)
![plantSS_Yellow](https://user-images.githubusercontent.com/81906237/167198953-97f15e09-6410-464a-9baa-8593a22a94e3.png)

- Escorpión:
![scorpionSS_Default](https://user-images.githubusercontent.com/81906237/167198918-ed0a173a-15ed-401b-8755-f0b74e81313e.png)

- Gato/Mapache:
![catSS_Default](https://user-images.githubusercontent.com/81906237/167198892-a0635e81-c60c-4a26-881a-fa46e7513ce1.png)


Además, cada enemigo cuenta con una spritesheet secundaria, que parpadea en blanco, para cuando están siento apuntados con la linterna.

# Referencias

- Pokemon (juegos antiguos)
- Animal Crossing
- Stardew Valley
- Memes de monos (especialmente)


# UML
![UML_Monkey_Delivery drawio](https://user-images.githubusercontent.com/82326243/152699560-aa794a2b-cd24-4e00-90fa-4dad823b08a2.png)


# Comunicación
Para la comunicación del equipo se usa un servidor de discord, con varios canales dedicados a diferentes partes del proyecto.
Además, se aprovechan las 4 horas semanales en clase presencial, para hacer una organización semanal del proyecto, y hacer un seguimiento de lo que cada uno está trabajando esa semana. 
![discord](https://user-images.githubusercontent.com/81906237/167201855-9c759f29-d37b-458c-b050-188b050764db.png)

# Pruebas

Para el testing del juego, buscábamos analizar cómo el jugador afrontaba las mecánicas y dinámicas básicas (moverse, aceptar misiones, interactuar con objetos, llegar al punto donde tiene que entregar la misión, etc) de la forma esperada: supiese manejarse dentro del juego con lo que nosotros le aportamos. Por otro lado era importante balancear los precios de los ítems de la tienda, y el dinero que ganas al hacer misiones, considerando la habilidad del jugador: si muere muchas veces y tarda mucho en hacer las misiones, ganará menos dinero que un jugador mejor.
Para ello realizamos un informe de pruebas, y un cuestionario que el tester rellenaría al acabar la prueba.

1- https://docs.google.com/document/d/1Bbtbw0Fj29UlRprhrWuNLlqLL6jAQiksbfh3qCFxdPg/edit?usp=sharing
Documento interno, que usamos para guiarnos en los cambios que deberíamos hacer según lo que observásemos del jugador.

2- https://docs.google.com/forms/d/e/1FAIpQLSdGS9mTBw7j24lcMTLKJwUnG7dSUgctUyDXw4PyPq_TqlKJzA/viewform
Formulario que los jugadores rellenaban, para dar feedback adicional.



