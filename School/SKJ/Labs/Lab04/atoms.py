import playground
import random


class Atom:
    def __init__(self, x, y, rad, color):
        """
        Inicializator třídy Atom
        :param x: souřadnice X
        :param y: soouřadnice Y
        :param rad: poloměr
        :param color: barva
        """
        self.coord_X = x
        self.coord_Y = y
        self.dim = rad # dimension
        self.color = color
        self.dir_X = 6
        self.dir_Y = 6
        pass

    def to_tuple(self):
        """Vrátí n-tici hodnot 
        příklad: x = 10, y = 12, rad = 15, color = 'green' -> (10,12,15,'green')
        """
        return (self.coord_X,self.coord_Y, self.dim, self.color)
         

    def move(self, width, height):

        if self.coord_X < 0 or self.coord_X + self.dim > width:
            self.dir_X *= -1 
             
        if self.coord_Y < 0 or self.coord_Y + self.dim > height:
            self.dir_Y *= -1 

        self.coord_X += self.dir_X
        self.coord_Y += self.dir_Y
              


class FallDownAtom(Atom):

    def __init__(self,  x, y, rad, color, acc, damp):
        super().__init__(x, y, rad, color)
        self.g = acc
        self.damping = damp

    def move(self, width, height):
            
            if self.coord_X < 0 or self.coord_X + self.dim > width:
                self.dir_X *= -1
             
            if self.coord_Y < 0 or self.coord_Y + self.dim > height:
                self.dir_Y *= -1
                self.dir_Y *= self.damping
                    


            self.coord_X += self.dir_X
            self.coord_Y += self.dir_Y
 
            self.dir_Y += self.g;


class ExampleWorld(object):

    def __init__(self, size_x, size_y, count):
        self.count = count
        self.width = size_x
        self.height = size_y
        colors = ['green', 'red', 'blue', 'orange', 'purple']
        self.atoms = [FallDownAtom(random.randint(5, self.width - 20), random.randint(5, self.height - 20), random.randint(5,20) ,colors[random.randint(0,len(colors) - 1)],  3, 0.8) for i in range(count)]

    def random_atom(self):
 
        pass

    def tick(self): 

        for i in range(self.count):
            self.atoms[i].move(self.width, self.height)

        tuples = []

        for i in range(self.count):
            tuples.append( self.atoms[i].to_tuple())

        return (tuples)


if __name__ == '__main__':
    size_x, size_y = 700, 400

    world = ExampleWorld(size_x, size_y, 5)
    playground.run((size_x, size_y), world)


