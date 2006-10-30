
class Array
  def scale( factor ) 
    self.map! { |element| element * factor }
  end
  def add( other )
    if self.size != other.size
      puts "bitch here"
    else
      for i in 1..self.size
        self[i] += other[i]
      end
    end
  end
end

def testArray()
  anArray = [ 1.0, 2.0 ]
  print "before scaling: "
  p anArray
  anArray.scale(3.0)
  print "after scaling: "
  p anArray

end

#testArray()
