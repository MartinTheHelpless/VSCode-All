import java.util.Objects;

class Film {
    private final String nazev;
    private final String reziser;
    private final int rokVydani;
    private final String zanr;
    private final String zeme;
    private final StavFilmu stav;

    private Film(Builder builder) {
        this.nazev = builder.nazev;
        this.reziser = builder.reziser;
        this.rokVydani = builder.rokVydani;
        this.zanr = builder.zanr;
        this.zeme = builder.zeme;
        this.stav = builder.stav;
    }

    public String getNazev() { return nazev;}

    public String getReziser() { return reziser; }

    public int getRokVydani() { return rokVydani;  }

    public String getZanr() { return zanr;}

    public String getZeme() { return zeme; }

    public StavFilmu getStav() { return stav; }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Film film = (Film) o;
        return rokVydani == film.rokVydani &&
                Objects.equals(nazev, film.nazev) &&
                Objects.equals(reziser, film.reziser) &&
                Objects.equals(zanr, film.zanr) &&
                Objects.equals(zeme, film.zeme) &&
                stav == film.stav;
    }

    @Override
    public int hashCode() {
        return Objects.hash(nazev, reziser, rokVydani, zanr, zeme, stav);
    }

    static class Builder {
        private final String nazev;
        private final String reziser;
        private final int rokVydani;
        private String zanr;
        private String zeme;
        private StavFilmu stav;

        Builder(String nazev, String reziser, int rokVydani) {
            this.nazev = nazev;
            this.reziser = reziser;
            this.rokVydani = rokVydani;
        }

        Builder zanr(String zanr) {
            this.zanr = zanr;
            return this;
        }

        Builder zeme(String zeme) {
            this.zeme = zeme;
            return this;
        }

        Builder stav(StavFilmu stav) {
            this.stav = stav;
            return this;
        }

        Film build() {
            return new Film(this);
        }
    }

    enum StavFilmu {
        NOVY,
        VYDANY,
        ODSTRANENY
    }
}

class NovinkyFilm extends Film {
    private final boolean maTrailery;

    NovinkyFilm(Builder builder) {
        super(builder);
        this.maTrailery = builder.maTrailery;
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof NovinkyFilm)) return false;
        if (!super.equals(o)) return false;
        NovinkyFilm that = (NovinkyFilm) o;
        return maTrailery == that.maTrailery;
    }

    @Override
    public int hashCode() {
        return Objects.hash(super.hashCode(), maTrailery);
    }

    static class Builder extends Film.Builder {
        private boolean maTrailery;

        Builder(String nazev, String reziser, int rokVydani) {
            super(nazev, reziser, rokVydani);
        }

        Builder maTrailery(boolean maTrailery) {
            this.maTrailery = maTrailery;
            return this;
        }

        @Override
        NovinkyFilm build() {
            return new NovinkyFilm(this);
        }
    }
}

class FilmTest {
    public static void main(String[] args) {
        Film film1 = new Film.Builder("Matrix", "Lana Wachowski", 1999)
                .zanr("Sci-Fi")
                .zeme("USA")
                .stav(Film.StavFilmu.VYDANY)
                .build();

        NovinkyFilm novinkyFilm1 = new NovinkyFilm.Builder("Interstellar", "Christopher Nolan", 2014)
                .zanr("Sci-Fi")
                .zeme("USA")
                .stav(Film.StavFilmu.VYDANY)
                .maTrailery(true)
                .build();

        System.out.println("Film1 a novinkyFilm1 jsou shodné: " + film1.equals(novinkyFilm1));
    }
}
