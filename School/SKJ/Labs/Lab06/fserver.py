from xmlrpc.server import SimpleXMLRPCServer

class Forecast(object):
    """
    Reprezentuje predpoved. V instancnich promennych jsou reprezentovany hodnoty
    predpovedi.
    """

    def __init__(self, description, wind_force, temperature):
        """
        Konstuktor predpovedi. Instancni promenne reprezentuji predana data.
        """
        self.description = description
        self.wind_force = wind_force
        self.temperature = temperature
        pass

    def get_list(self):
        """
        Vraci trojici reprezentujici predpoved.
        """
        return "What weather feels like: " + str(self.description) + "\nWind Force: " + str(self.wind_force) + "\nTemperature Feel: " + str(self.temperature) + "\n--------------------------------------------------\n"

class ForecastCalendar(object):
    """
    Reprezentuje predpovedi pro nekolik dni. Data predpovedi jsou ulozena ve
    slovniku. Klicem je datum, hodnotou pak instance trody Forecast. Vkladani
    predpovedi metodou update_forecast je chraneno heslem, ktere je predano v
    konstruktoru. Startovaci data jsou tezz predana v konstruktoru.
    """
    
    def __init__(self, initial_values, password):
        """
        Konstruktor kalendare predpovedi. Instancni promenne reprezentuji predana data.
        """
        self.initial_values = initial_values
        self.password = password
        pass

    def get_forecast(self, date):
        """
        Vrati predpoved pro zadane datum jako retezec. V pripade, ze pro dane
        datum neexistuje predpoved. Vrati se retezec "No focecast".
        """
        if date in self.initial_values:
            return self.initial_values[date].get_list()
        return "No forecast"

    def update_forecast(self, password, date, description, wind_force, temperature):
        """
        Aktualizuje predpoved pro zadane datum. Akce je chranena heslem. Pokud
        heslo nesouhlasi s heslem, ktere je zadano v konstruktoru, neni mozno
        aktualizovat predpoved. v takovm priapde metoda vrati retezec "No
        update". Metoda muze aktualizovat stavajici predpoved nebo pridat novou.
        """

        if self.password == password:
            if date in self.initial_values:
                self.initial_values[date] = Forecast(description, wind_force, temperature)
        
def main():

    # TODO Pridat do initial_state data predpovedi tak, aby je mohl klient precist.
    initial_state = {
        "2012-11-05":Forecast("Underwater Dungeon In Here", 4, 20.3),
        "2012-11-06":Forecast("Windy AF", 4, 20.3),
        "2012-11-07":Forecast("Temporary Wetness", 4, 20.3),
        "2012-11-08":Forecast("Dry As The Chicken Leftovers", 4, 20.3),
        "2012-11-09":Forecast("Its Fookin Wimdy", 4, 20.3),
        "2012-11-10":Forecast("Wizard Dropped his Weather Staff", 4, 20.3),
        "2012-11-11":Forecast("Look Out Your Window Man. Cmon ...", 4, 20.3),
        "2012-11-12":Forecast("Looks Like Rain", 4, 20.3),
        "2012-11-13":Forecast("It's A Non-Sunny Day!", 4, 20.3)
    }

    fcalendar = ForecastCalendar(initial_state, password = "master-of-weather")

    server_address = ('localhost', 10001)
    server = SimpleXMLRPCServer(server_address)
    server.register_instance(fcalendar)
    server.register_introspection_functions()
    print("Starting Weather XML-RPC server, use <Ctrl-C> to stop")
    server.serve_forever()

if __name__ == "__main__":
    main()