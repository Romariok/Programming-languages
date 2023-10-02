package added.pokemon;

import added.moves.DazzlingGleam;
import ru.ifmo.se.pokemon.Type;

public class Sylveon extends Eevee{
    public Sylveon(String name, int level){
        super(name, level);
        setStats(95, 65, 65, 110, 130, 60);
        setType(Type.FAIRY);
        addMove(new DazzlingGleam());
    }
}
