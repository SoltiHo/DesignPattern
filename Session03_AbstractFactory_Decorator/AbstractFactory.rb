####################
#Interface Classes
####################

#Borrowed from http://metabates.com/2011/02/07/building-interfaces-and-abstract-classes-in-ruby/
module AbstractInterface
  class InterfaceNotImplementedError < NoMethodError
  end

  def self.included(klass)
    klass.send(:include, AbstractInterface::Methods)
    klass.send(:extend, AbstractInterface::Methods)
  end

  module Methods
    def api_not_implemented(klass)
      caller.first.match(/in \`(.+)\'/)
      method_name = $1
      raise AbstractInterface::InterfaceNotImplementedError.new("#{klass.class.name} needs to implement '#{method_name}' for interface #{self.name}!")
    end

  end
end

class ContinentAnimalFactory
  include AbstractInterface
  
  attr_reader(:validAnimals)
  
  def GetInstanceOfAnimal(type)
    raise Exception.new("#{type} does not exist for #{self.class.name}") unless @validAnimals.include?(type)
    return eval("#{self.to_s}::#{type.to_s}.new")
  end
end

class Animal
  include AbstractInterface
  
  attr_reader(:name)

  def mate(otherAnimal)
    Animal.api_not_implemented(self)
  end

  def evade(animal)
    Animal.api_not_implemented(self)
  end
end

class Herbrivore < Animal
  def graze()
    Herbrivore.api_not_implemented(self)
  end
end

class Predator < Animal
  def Hunt(otherAnimal)
    Herbrivore.api_not_implemented(self)
  end
end

########################
# Classes
########################
class NorthAmericaAnimalFactory < ContinentAnimalFactory
  def initialize()
    @validAnimals = [:Bison, :Wolf]
  end

  private

  class Wolf < Predator

  end

  class Bison < Herbrivore

  end
end

class AfricaAnimalFactory < ContinentAnimalFactory
  def initialize()
    @validAnimals = [:Lion, :Wildebeest]
  end

  private

  class Lion < Predator

  end

  class Wildebeest < Herbrivore

  end
end

########################
# Methods
########################

def runFoodChain(country)
  #Get the factory
  factory = eval(country.to_s + "AnimalFactory.new()")

  if factory.is_a? NorthAmericaAnimalFactory
    wolf = factory.GetInstanceOfAnimal(:Wolf)
    bison = factory.GetInstanceOfAnimal(:Bison)
  elsif factory.is_a? AfricaAnimalFactory
    lion = factory.GetInstanceOfAnimal(:Lion)
    wildebeest = factory.GetInstanceOfAnimal(:Wildebeest)

  end
end

runFoodChain(:NorthAmerica)
runFoodChain(:Africa)