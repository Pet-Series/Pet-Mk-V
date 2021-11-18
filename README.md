# Pet-Mk-V
<h1 align="center">Welcome to the Pet-Mk-V repository</h1>

ROS repository in the https://github.com/Pet-Series Git-Organizations.</br>
Containing multiply ROS-packages.

# Software/Setup Pet series micro robots #
The main objective/scope for this repository is to control the part of the software (and parameter settings) that is unique for this Pet Mark V (five) robot.
<table>
    <tr>Pet-Mk.V during developing.
      <td><img src="./doc/Pet-Mk.V Build Phase_10.jpg" width="350px"></td>
      <td></td>
    </tr>
  </table>

- **Simplification:** As MCU we mainly using Arduino compatible hardware, like Arduino UNO and Arduino NANO. 
- **Standardisation:** As system integration tool (Middle ware) we use ROS running on a Raspberry PI. Each MCU act as an ROS-serial device. 
- **Modularisation:** We have tried to make the code as generic/common as possible. 


# Drawing/Schemas:
<table>
  <tr>
    <td>
      <img src="./doc//Pet-Mk.V Circuit Diagram - Arduino UNO.jpg"  width="350px"><br>
      Circuit Diagram - UNO
    </td>
    <td>
      <img src="./doc/Pet-Mk.V Circuit Diagram - Arduino NANO.jpg" width="350px"><br>
      Circuit Diagram - NANO
    </td>
    <td>
      <img src="./doc/Pet-Mk.V Circuit Diagram - Main board.jpg"  width="350px"><br>
      Circuit Diagram - RPi
    </td>
  </tr>
  <tr>
    <td>
      <img src="doc/Pet-Mk.V Circuit Diagram - Power.jpg" width="350px"><br>
      PowerDistributionSchema</td>
    <td>
    </td>
    <td>
    </td>
  </tr>
</table>

# External references
- http://wiki.ros.org/
- http://wiki.ros.org/rosserial

For my own convenience - Some GitHub cheat sheets
- https://guides.github.com/features/mastering-markdown/
- https://help.github.com/en/github/writing-on-github/basic-writing-and-formatting-syntax
- https://www.webfx.com/tools/emoji-cheat-sheet/