#include <stdlib.h> /* malloc, free */
#include <assert.h>
#include <errno.h>

#include "c_buffer.h"

#define WRITE_GAP 1
#define INCREMENT_IN_LOOP(x) cb->base + (((cb->x - cb->base) + 1) % (cb->top - cb->base))

struct c_buffer_s
{
	char *base;
	char *top;
	char *read;
	char *write;
};

c_buffer_t *CBufferCreate(size_t capacity)
{
	c_buffer_t *buffer = malloc(sizeof(c_buffer_t) + capacity + WRITE_GAP);

	if (buffer)
	{
		buffer->base = (char*)buffer + sizeof(c_buffer_t);
		buffer->top = (char*)buffer + sizeof(c_buffer_t) + capacity + WRITE_GAP;
		buffer->read = buffer->base;
		buffer->write = buffer->base;
	}

	return (buffer);
}

void CBufferDestroy(c_buffer_t **cb)
{
	assert(*cb);

	free(*cb);

	*cb = NULL;
}

void CBufferClear(c_buffer_t *cb)
{
	assert(cb);

	cb->read = cb->base;
	cb->write = cb->base;
}

ssize_t CBufferWrite(c_buffer_t *cb, const void *src, size_t nbyte)
{
	size_t write_space = 0;
	size_t bytes_to_write = 0;
	size_t bytes_written = 0;

	const char* src_ptr = src;

	assert(src);
	assert(cb);

	if (cb->write < cb-> read)
	{
		write_space = cb->read - cb->write - WRITE_GAP;
	}
	else
	{
		write_space = (cb->read - cb->base) + (cb->top - cb->write) - WRITE_GAP;
	}

	if (0 == write_space)
	{
		errno = ENOBUFS;
		return (-1);
	}

	bytes_to_write = (write_space > nbyte) ? nbyte : write_space;
	bytes_written = bytes_to_write;

	while (bytes_to_write > 0)
	{
		*(cb->write) = *src_ptr;
		cb->write = INCREMENT_IN_LOOP(write);
		++src_ptr;
		--bytes_to_write;
	}

	return (bytes_written);
}

ssize_t CBufferRead(c_buffer_t *cb, void *dest, size_t nbyte)
{
	size_t bytes_to_read = 0;
	size_t bytes_read = 0;

	char* dest_ptr = dest;

	assert(dest);
	assert(cb);

	if (cb->read <= cb->write)
	{
		bytes_to_read = cb->write - cb->read;
	}
	else
	{
		bytes_to_read = (cb->top - cb->read) + (cb->write - cb->base);
	}

	if (0 == bytes_to_read)
	{
		errno = ENODATA;
		return (-1);
	}

	bytes_to_read = (bytes_to_read > nbyte) ? nbyte : bytes_to_read;
	bytes_read = bytes_to_read;

	while (bytes_to_read > 0)
	{
		*dest_ptr = *(cb->read);
		cb->read = INCREMENT_IN_LOOP(read);
		++dest_ptr;
		--bytes_to_read;
	}

	return (bytes_read);
}

size_t CBufferGetSize(const c_buffer_t *cb)
{
	assert(cb);

	return ((cb->read <= cb->write) ?
			(cb->write - cb->read) :
		   ((cb->top - cb-> read) + (cb->write - cb->base)));
}

size_t CBufferGetCapacity(const c_buffer_t *cb)
{
	assert(cb);

	return (cb->top - cb->base - WRITE_GAP);
}
