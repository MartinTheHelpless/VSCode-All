public class DomesticDog extends Canidae {

    private String owner;

    public DomesticDog(String owner, String hairColor, int hairLength){
        super(hairColor, hairLength);
        this.owner = owner;
    }
    public String getOwner() {
        return owner;
    }

    public String getDescription(){
        super.getDescription();
        return (", Owner: " + this.owner);
    }

}
