package added.pokemon;

import ru.ifmo.se.pokemon.Type;

public class Florges extends Floette{
    public Florges(String name, int level){
        super(name, level);
        setStats(78, 65, 68, 112, 154, 75);
        addType(Type.FAIRY);
    }
}
