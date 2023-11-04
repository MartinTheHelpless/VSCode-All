public class Canidae implements Descriptable{

    private String hairColor;
    private int hairLength;

    public Canidae(String hairColor){
        this.hairColor = hairColor;
    }

    public Canidae(String hairColor, int hairLength){
        this.hairColor = hairColor;
        this.hairLength = hairLength;
    }

    public int getHairLength() {
        return hairLength;
    }

    public String getHairColor() {
        return hairColor;
    }

    @Override
    public String getDescription() {
        return ("Hair color: " + this.hairColor + ", Hair length: " + this.hairLength);
    }

}
