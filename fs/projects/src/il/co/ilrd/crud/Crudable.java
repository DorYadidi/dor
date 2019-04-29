package il.co.ilrd.crud;

import java.io.Serializable;

public interface Crudable<ID extends Serializable, T extends Serializable> extends AutoCloseable {
	public ID create(T data);

	public void update(ID id, T data);

	public T read(ID id);

	public void delete(ID id);
}
