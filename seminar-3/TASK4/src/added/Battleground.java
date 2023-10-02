package added;

import ru.ifmo.se.pokemon.*;
import added.pokemon.*;

public class Battleground {
    public static void main(String[] args) {
        Battle b = new Battle();
        b.addAlly(new Heatran("Heatran", 1));
        b.addAlly(new Eevee("Eevee", 1));
        b.addAlly(new Sylveon("Sylveon", 1));
        b.addFoe(new Flabebe("Flabebe", 1));
        b.addFoe(new Floette("Floette", 1));
        b.addFoe(new Florges("Florges", 1));
        b.go();
    }
}