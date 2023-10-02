package added.moves;
import ru.ifmo.se.pokemon.*;
public class ScaryFace extends StatusMove{
    public ScaryFace(){
        super(Type.NORMAL, 0, 100);
    }
    @Override
    protected void applyOppEffects(Pokemon p){
        Effect e = new Effect().stat(Stat.SPEED, -2);
        p.addEffect(e);
    }
    @Override
    protected String describe(){
        return "uses Scary Face";
    }
}
