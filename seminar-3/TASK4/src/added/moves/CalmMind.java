package added.moves;
import ru.ifmo.se.pokemon.*;
public class CalmMind extends StatusMove{
    public CalmMind(){
        super(Type.PSYCHIC, 0, 100);
    }
    @Override
    protected void applySelfEffects(Pokemon p){
        Effect e = new Effect().stat(Stat.SPECIAL_ATTACK, +1).stat(Stat.SPECIAL_DEFENSE, +1);
        p.addEffect(e);
    }
    @Override
    protected String describe(){
        return "uses Calm Mind";
    }
}