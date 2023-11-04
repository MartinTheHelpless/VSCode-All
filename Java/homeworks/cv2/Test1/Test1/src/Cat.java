public class Cat implements Descriptable{
    private double weight;
    private String species;

    public Cat(String species, int weight) {
        this.species = species;
        this.weight = weight;
    }

    public double getWeight() {
        return this.weight;
    }

    public String getSpecies() {
        return this.species;
    }

    @Override
    public String getDescription() {
        return (this.species + ", Weight: " + this.weight);
    }
}
