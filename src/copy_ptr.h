#ifndef copy_ptr_h
#define copy_ptr_h

/*
    Alexander: a neural networks library
    Copyright (C) 2011-2012  Jack Hall

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    e-mail: jackwhall7@gmail.com
*/

/*
	I found these class templates online when I was trying figure out
	how to get STL containers to accept polymorphic objects. These are
	copied for the most part, but I did add move-awareness to the poly 
	class. 
*/

namespace alex {

	template <typename T>
	struct poly_base {

		virtual ~poly_base() {}         // support derivation
		virtual poly_base* clone() = 0; // copy derived object
		virtual T& get_object() = 0;    // stored in derived
	}; //struct poly_base



	template <typename T, typename S>
	struct poly_object : public poly_base<T> {

		poly_object(S const& s) : object(s) {}
		poly_base<T>* clone() { return new poly_object(*this); }
		T& get_object() { return object; }
	
	private:
		S object;
	}; //struct poly_object



	template <typename T>
	struct poly {

		poly(): ptr(0) {}                 // no object by default
	  
		template <typename S> 		// creation from prototype
		poly(S const& s) : ptr(new poly_object<T, S>(s)) {}
	 
		poly(poly const& p) : ptr(p.ptr->clone()) {}   // create a cloned object
		poly(poly&& p) : ptr(p.ptr) { p.ptr = 0; }
	  
		~poly() { delete ptr; }           // release current object
	   
		poly& operator=(poly const& p) { // assign cloned object
			poly_base<T>* tmp = p.ptr->clone();
			std::swap(ptr, tmp);
			delete tmp;
			return *this;
	    	}
	    	
	    	poly& operator=(poly&& p) { 
	    		ptr = p.ptr;
	    		p.ptr = 0;
	    	}
	   
		// Accessors to the hold object:
		T& operator*() const { return ptr->get_object(); }
		T* operator->() const { return &(ptr->get_object()); }
	
	private:
		poly_base<T>* ptr;
	}; //struct poly

} //namespace alex

#endif

